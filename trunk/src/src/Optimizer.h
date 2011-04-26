#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_

#include <map>
#include <utility>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include "ParseTree.h"
#include "EventLogger.h"
#include "Statistics.h"
#include "QueryPlan.h"
#include "Record.h"
#include "Schema.h"

using namespace std;


#define _ESTIMATOR_DEBUG 1

class Optimizer
{
private:
	// members
	struct FuncOperator * m_pFuncOp;
	struct TableList * m_pTblList;
	struct AndList * m_pCNF;

	int m_nNumTables, m_nGlobalPipeID;
	vector <string> m_vSortedTables;
	vector <string> m_vSortedAlias;
	char ** m_aTableNames;
	vector <string> m_vWholeCNF;	// break the AndList into tokens
	map <string, pair <Statistics *, QueryPlanNode*> > m_mJoinEstimate;
	Statistics m_Stats;

	// functions
	Optimizer();
	int SortTables();
	int SortAlias();
	void TokenizeAndList();
	void PrintTokenizedAndList();	// TODO: delete this
	void PopulateTableNames(vector <string> & vec_rels);	// in m_aTableNames char** array
	void ComboToVector(string, vector <string> & vec_rels); // breal A.B.C into vector(A,B,C)
	void TableComboBaseCase(vector <string> &);
	int ComboAfterCurrTable(vector<string> &, string);
	void PrintFuncOpRecur(struct FuncOperator *func_node);


public:
	Optimizer(struct FuncOperator *finalFunction,
			  struct TableList *tables,
			  struct AndList * boolean,
			  Statistics & s);
	~Optimizer();

	void PrintFuncOperator();
	void PrintTableList();
	vector<string> PrintTableCombinations(int combo_len);
	
};

#endif