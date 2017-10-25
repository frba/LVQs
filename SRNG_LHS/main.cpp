/* 
 * File:   main.cpp
 * Author: flavia
 *
 * Created on 10 de Março de 2015, 17:00
 */

#include <iomanip>

#include "LatinHypercubeSampling.h"
#include "GRLVQ.h"
#include "SRNG.h"
#include "ArffData.h"

#define RG_MIN 0 
#define RG_MAX 1 

#define NNODES 0
#define ATP 1
#define ATN 2
#define AW 3
#define TAU 4
#define EPOCHS 5
#define SEED 6
#define GAMMA 7

using namespace std;
int classIndex = -1; // Class index: 0 firts column; -1 last column
int nCls = 2; //Number of classes in data

string filein;
string fileout;


void printContigencyTable(MatVector<int> &colIndexes, MatVector<float> &values, MatMatrix<float> &data, vector<int> &classes){
    MatMatrix<int> result(pow(values.size(), colIndexes.size()), colIndexes.size() + 2);
    result.fill(0);
    
    //Fill first cols
    int alter=1;
    for (int j=0; j < result.cols()-2; j++) {
        int v=0;
        for (int i=0; i < result.rows(); i++) {
            result[i][j] = values[v];
            if ((i+1)%alter==0) v++;
            if (v>values.size()-1) v = 0;
        }
        alter = alter*values.size();
    }
    
    //Fill case/ctrl cols from data
    for (int r=0; r<data.rows(); r++) {
        for (int i=0; i < result.rows(); i++) {
            bool match=true;
            for (int j=0; j < result.cols()-2; j++) {
                if (data[r][colIndexes[j]]!=result[i][j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
               if (classes[r]==0) {
                   result[i][result.cols()-2]++;
               }
               else {
                   result[i][result.cols()-1]++;
               }
               break;
            }
        }
    }
    
    //calculate Entropy
    double entropy = 0; double pmf = 0;
    
    for (int i=0; i < result.rows(); i++) {
        for (int j=1; j < result.cols(); j++)  {
            
            if (result[i][j] != 0){
                pmf = (double)result[i][j]/data.rows();
                entropy = - entropy + ((pmf) * log(pmf));
                
            }
        }
        dbgOut(2) << endl;
    }
    dbgOut(2) << endl;
    dbgOut(2) << entropy << endl;
    
    
    //calculate confusion matrix
    MatMatrix<float> m_confusion(2,2);
    m_confusion.fill(0);
    int t_case = 0;
    int t_control = 0;
    
    for (int i=0; i < result.rows(); i++) {
        t_case = result[i][result.cols()-1];
        t_control = result[i][result.cols() - 2];
                
        if (t_case > t_control) {
            m_confusion[1][1] += t_case;
            m_confusion[1][0] += t_control;
        }
        if (t_control > t_case) {
            m_confusion[0][0] += t_control;
            m_confusion[0][1] += t_case;
        }
    }
    
    //calculate metrics
    float tp, tn, fp, fn = 0;
    tp = m_confusion[1][1];
    tn = m_confusion[0][0];
    fn = m_confusion[1][0];
    fp = m_confusion[0][1];
    
    //Accuracy
    float acc = 0;
    acc = (tn + tp)/(tn + tp + fn + fp);
    
    //Precision
    float precision = 0;
    precision = (tp)/(tp+fp);
    
    //Recall
    float recall = 0;
    recall = tp/(tp+fn);
    
    //F1
    float f1 = 0;
    f1 = (2*tp)/((2*tp) + fp + fn);
    
    //Fmeasure
    float odd = 0;
    odd = (tp/fp)/(fn/tn);
    
    float oddsq = 0;
    oddsq = sqrt((1/tp)+(1/fn)+(1/fp)+(1/tn));
    
    //
    
    //print confusion matrix
    for (int i=0; i < m_confusion.rows(); i++) {
        for (int j=0; j < m_confusion.cols(); j++)  {
            dbgOut(0) << m_confusion[i][j] << "\t";
        }
        dbgOut(0) << endl;
    }
    dbgOut(0) << acc << "\t" << precision << "\t" << recall << "\t" << f1 <<  "\t";
    dbgOut(0) << tp << "\t" << tn << "\t" << fp << "\t" << fn;
    dbgOut(0) << endl;
    
    
    
}

bool printNMax(SRNG &srng, int nNodes, int i, int epochs, unsigned int seed) {
    int n = srng.weight.size();
    MatVector<float> relevances = srng.weight;
    
    std::stringstream filenameout;
    filenameout << fileout << i << ".txt";
    
    ofstream file(filenameout.str().c_str());
    if(!file.is_open()){
        dbgOut(0) << "Error openning training file" << endl;
        return false;
    }
    dbgOut(0) << "Relevancias em: " << filenameout.str().c_str() << endl;
    
    //Print parameters in file
    file << std::fixed << std::setprecision(7);
    file << "Vizinhanca:\t" << srng.gamma << endl;
    file << "Numero de Nodos:\t" << nNodes << endl;
    file << "T.A Positiva:\t" << srng.alpha_tp0 << endl;
    file << "T.A Negativa:\t" << srng.alpha_tn0 << endl;
    file << "T.A Peso:\t" << srng.alpha_w0 << endl;
    file << "T. Decaimento:\t" << srng.tau << endl;
    file << "Numero de Epocas:\t" << epochs  << endl;
    file << "Semente:\t" << seed << endl << endl;
    
    //Print n max relevances
    float max = -1;
    int index = 0;
    for (int i=0; i<n; i++) {
        for (int c=0; c<relevances.size(); c++) {
            if (relevances[c]>max) {
                max = relevances[c];
                index = c;
            }
        }
        
        dbgOut(2) << index << "\t" << max << "\n";
        file << index << "\t" << max << endl;
        relevances[index] = -1;
        max = -1;
    }
    dbgOut(2) << endl;
    file.close();
    
    return true;
}

bool trainLVQ(MatMatrix<float> &trainingData, vector<int> &classes, SRNG &srng, int nNodes, int epochs, unsigned int seed) {
   
    srng.data = trainingData;
    srng.vcls = classes;
    srng.tmax = epochs*trainingData.rows();
    
    //Initialize LVQ
    srand(seed);
    srng.initialize(nNodes, nCls, trainingData.cols());
    
//    //Print nodes positions
//    dbgOut(2) << "Initial Positions: " << endl;
//    for (LVQNode *node = srng.getFirstNode(); !srng.finished(); node = srng.getNextNode()) {
//        dbgOut(2) << "Node: " << "[" << node->w[0] << ", " << node->w[1] << ", " << node->w[2] << "]" << ": " << node->cls << endl;
//    }
    
    
    //Print parameters
    dbgOut(2) << std::fixed << std::setprecision(15);
    dbgOut(2) << "Numero de Nodos: " << nNodes << endl;
    dbgOut(2) << "T.A Positiva: " << srng.alpha_tp0 << endl;
    dbgOut(2) << "T.A Negativa: " << srng.alpha_tn0 << endl;
    dbgOut(2) << "T.A Peso: " << srng.alpha_w0 << endl;
    dbgOut(2) << "T. Decaimento: " << srng.tau << endl;
    dbgOut(2) << "Numero de Epocas: " << epochs << endl;
    dbgOut(2) << "Semente: " << seed << endl;
    dbgOut(2) << "Gamma: " << srng.gamma << endl;
    
    srng.trainning(srng.tmax);
  
//    //Print nodes positions
//    dbgOut(2) << endl << "Final Positions: " << endl;
//    for (LVQNode *node = srng.getFirstNode(); !srng.finished(); node = srng.getNextNode()) {
//        dbgOut(2) << "Node: " << "[" << node->w[0] << ", " << node->w[1] << ", " << node->w[2] << "]" << ": " << node->cls << endl;
//    }
    return true;
}

bool trainSRNG(SRNG &srng, int nNodes, int epochs, unsigned int seed, MatMatrix<float> &trainingData, vector<int> &classes, map<int,int> &labels) {
    
    //MatMatrix<float> trainingData;
    //vector<int> classes;
    //map<int,int> labels;
    
    //Read data
    //if (!ArffData::readArffBD(filein, trainingData, labels, classes, classIndex)) {
    //   dbgOut(0) << "Error openning training file" << endl;
    //    return false;
    //}
    
    //Normalize data
    //ArffData::rescaleCols01(trainingData, 0, 2);
    
    //trainingData.mult(2); //Move data to: 0 <-> 2
    //trainingData.add(-1);  //Move data to: -1 <-> 1
   
    srng.data = trainingData;
    srng.vcls = classes;
    srng.tmax = epochs*trainingData.rows();
    
    //Initialize LVQ
    srand(seed);
    srng.initialize(nNodes, nCls, trainingData.cols());
    srng.saveLVQ("teste.lvq");
       
    srng.trainning(srng.tmax);

    return true;
}

double round(double n, unsigned d){
    return floor(n * pow(10., d) + .5) / pow(10., d);
} 

void evaluateResults(MatMatrix<float> &trainingData, vector<int> &classes, GRLVQ &rootLVQ, MatVector<int> &winers, MatVector<float> &nodeScore) {
    //Evaluate results
    
    for (int i=0; i<trainingData.rows(); i++) {
        MatVector<float> row;
        trainingData.getRow(i, row);
        
        LVQNode *node = rootLVQ.getWinner(row);
        winers[i] = node->getId();
    }
    
    for (int j=0; j<rootLVQ.size(); j++) {
        int cont=0, cas=0;
        
        for (int i=0; i<trainingData.rows(); i++)
            if (winers[i]==j) {
                if (classes[i]==0)
                    cont++;
                else
                    cas++;
            }
        
        if (cas*cont>0) {
            nodeScore[j] = ((float)min(cas, cont))/((float)max(cas, cont));
        } else nodeScore[j] = 0;
        
        dbgOut(0) << "Node " << j << ": " << nodeScore[j] << " - " << cas << "/" << cont << endl;
    }    
}

void selectNodeDataset(MatVector<int> &winers, int nodeIndex, MatMatrix<float> &trainingData, vector<int> &classes, MatMatrix<float> &selData, vector<int> &selClass) {
        
    selClass.clear();
    selData.clear();
    for (int i=0; i<winers.size(); i++) {
        if (winers[i]==nodeIndex) {
            MatVector<float> row;
            trainingData.getRow(i, row);
            selData.concatRows(row);
            selClass.push_back(classes[i]);
        }
    }
}

bool openFile(MatMatrix<float> &trainingData, vector<int> &classes, map<int,int> &labels){

    //Read data
    if (!ArffData::readArffBD(filein, trainingData, labels, classes, classIndex)) {
        dbgOut(0) << "Error openning training file" << endl;
        return false;
    }
    
    //Normalize data
    ArffData::rescaleCols01(trainingData, 0, 2);
        
    return true;
}

void printRank(int n, MatVector<float> rel){
    
    int count;
    
    for(int i=0; i<n; i++){
        count = 0;
        for(int j=0; j<rel.size(); j++){
            if(rel[i] < rel[j]){
                count++;
            }
        }
        dbgOut(0) << "[" << i << "]: " << rel[i] << " " << "[" << count << "]" << endl;
    }
    dbgOut(0) << endl;
}


void printRelevant(int n, MatVector<float> rel) {

    
    dbgOut(0) << "Correct cols relevances: ";
    for (int i=0; i<n; i++) {
        dbgOut(0) << rel[i] << " ";
    }
    
    dbgOut(0) << endl << "Max: ";
    for (int i=0; i<n; i++) {
        unsigned int index;
        float max = rel.max(index); 
        dbgOut(0) << index << "(" << max << ") ";
        rel[index]=0;
    }
    dbgOut(0) << endl;
    
}

int testAcuracy(){
    MatMatrix<float> trainingData;
    vector<int> classes;
    map<int,int> labels;
    
    //Read data
    if (!ArffData::readArffBD(filein, trainingData, labels, classes, classIndex)) {
        dbgOut(0) << "Error openning training file" << endl;
        return false;
    }
    
    MatMatrix<float> trainingDataOrig(trainingData);
    MatVector<int> colIndexes;
    MatVector<float> values(3);
    values[0] = 0; values[1] = 1; values[2] = 2;
    
    for (int i=0; i<2; i++){
        colIndexes.append(i);
        dbgOut(0) << i << ": " << endl;
        printContigencyTable(colIndexes, values, trainingDataOrig, classes);
        
    }
    
}

int testSRNG() {
    
    MatMatrix<float> trainingData;
    vector<int> classes;
    map<int,int> labels;
    
    //Read data
    if (!ArffData::readArffBD(filein, trainingData, labels, classes, classIndex)) {
        dbgOut(0) << "Error openning training file" << endl;
        return false;
    }
   
    SRNG srng;

    int nNodes = 35;
    srng.gamma = 0.7; //Parametro da Vizinhanca
    srng.h_threshold = 0.001; //Threshold da Vizinhanca
    srng.alpha_tp0 = 0.45; //0.0005; //Learning rate positive
    srng.alpha_tn0 = 0.05;  //0.0001; //Learning rate negative
    srng.alpha_w0 = 0.4; //0.0001; //Learning rate relevances
    srng.tau = 0.00001;
    int epochs = 3500; //5500
    unsigned int seed = 583;//7
    
    
    MatMatrix<float> trainingDataOrig(trainingData);
    MatVector<int> colIndexes(6);
    colIndexes[0] = 0; colIndexes[1] = 1; colIndexes[2] = 2; colIndexes[3] = 3; colIndexes[4] = 4; colIndexes[5] = 5;
    MatVector<float> values(3);
    values[0] = 0; values[1] = 1; values[2] = 2;
    
    printContigencyTable(colIndexes, values, trainingDataOrig, classes);
    
    //Normalize data
    ArffData::rescaleCols01(trainingData);
    
    //trainingData.mult(2); //Move data to: 0 <-> 2
    //trainingData.add(-1);  //Move data to: -1 <-> 1

    //Train LVQ
    trainLVQ(trainingData, classes, srng, nNodes, epochs, seed);
    srng.enumerateNodes();
    
    MatVector<int> winers(trainingData.rows());
    MatVector<float> nodeScore(srng.size());
    
    //Print Results
    printNMax(srng, nNodes, 0, epochs, seed);
    evaluateResults(trainingData, classes, srng, winers, nodeScore);
    printRelevant(15, srng.weight);
    dbgOut(0) << "\nMax final results: " << endl;
    
    //Print winner's contigency table 
   
    for(int i=0; i<3; i++){
        unsigned int index;
        srng.weight.max(index);
        colIndexes[i] = index;
        srng.weight[index]=0;
        dbgOut(0) << colIndexes[i] << endl;
    }
    //printContigencyTable(colIndexes, values, trainingDataOrig, classes); 
    //printRank(3, srng.weight);
    //dbgOut(0) << "Seed: " << seed << endl;
}

void runLHS(){
        MatMatrix<float> trainingData;
        vector<int> classes;
        map<int,int> labels;
        
	MatMatrix<double> ranges(8, 2);
        ranges[GAMMA][RG_MIN] = 0.6; ranges[GAMMA][RG_MAX] = 0.7; //0.01 a 1
	ranges[NNODES][RG_MIN] = 20; ranges[NNODES][RG_MAX] = 50; //2 a 10
	ranges[ATP][RG_MIN] = 0.45; ranges[ATP][RG_MAX] = 0.5;      
	ranges[ATN][RG_MIN] = 0.025; ranges[ATN][RG_MAX] = 0.04; //0.001 a 0.5  
	ranges[AW][RG_MIN] = 0.15; ranges[AW][RG_MAX] = 0.2; //0.01 a 0.5
	ranges[TAU][RG_MIN] = 0.00001; ranges[TAU][RG_MAX] = 0.000014; //0.00001 a 0.01
	ranges[EPOCHS][RG_MIN] = 5000; ranges[EPOCHS][RG_MAX] = 10000;
        ranges[SEED][RG_MIN] = 0; ranges[SEED][RG_MAX] = 1000;
        
	int L = 100; //Number of parameters sorted
	MatMatrix<double> lhs;
	LHS::getLHS(ranges, lhs, L); //Create matrix lhs with parameters
        
        //Open File
        openFile(trainingData, classes, labels);

	for (int i=0;i<L;i++) { // For each set of parameters
                SRNG srng;
                srng.h_threshold = 0.001;
                srng.gamma = lhs[i][GAMMA];
		int nNodes = lhs[i][NNODES]; //Number of nodes created in map
		srng.alpha_tp0 = round(lhs[i][ATP], 7); //0.0005; //Learning rate positive
		srng.alpha_tn0 = round(lhs[i][ATN], 7);  //0.0001; //Learning rate negative
		srng.alpha_w0 = round(lhs[i][AW], 7); //0.0001; //Learning rate relevances
		srng.tau = round(lhs[i][TAU], 7);
		int epochs = lhs[i][EPOCHS];
                unsigned int seed = (unsigned int) lhs[i][SEED];
                
                //Train LVQ
		trainSRNG(srng, nNodes, epochs, seed, trainingData, classes, labels);
		
                //Print Results
                printNMax(srng, nNodes, i, epochs, seed);
                
                //Print Positions of Revelant SNPs
                printRank(5, srng.weight);
	}
}


int main(int argc, char** argv) {

    dbgThreshold(0);
        
    if(argc < 2){
        dbgOut(0) << "Use: lvqlhs filein fileout" << endl;
        return -1;
    }
    filein = argv[1];
    fileout = argv[2];
    
    srand(0);
    //testSRNG();
    //testAcuracy();
    runLHS();
    
    return 0;
}