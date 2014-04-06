#include "svmex.h"
 

//convert vector to struct svm_node array format
void ConvertToLibSVMFormat (std::vector<int>& features,std::vector<int>& missing_feature_flag, struct svm_node* _x)
{
	int count = features.size();	int k =0;
	for (int i=0; i<count; i++)
	{
		if (missing_feature_flag[i] == -1) continue;

		_x[k].index = i+1;
		_x[k].value = features[i];
		k++;
	}
	//index = -1 indicates the end of one vector
	_x[k].index = -1;
}

//convert vector to struct svm_node array format
void ConvertToLibSVMFormat (double* features, bool* missing_feature_flag, int count, struct svm_node* _x)
{
	int k = 0;
	for (int i =0; i<count; i++)
	{
		if (missing_feature_flag[i]) continue;

		_x[k].index = i+1;
		_x[k].value = features[i];
		k++;
	}
	//index = -1 indicates the end of one vector
	_x[k].index = -1;
}

//convert vector to struct svm_node array format(without missing_feature_flag)
void ConvertToLibSVMFormat(std::vector<float>& features, int count, struct svm_node* _x)
{
	int k = 0;
	for (int i =0; i<count; i++)
	{		
		_x[k].index = i+1;
		_x[k].value = (double)features[i];
		k++;
	}
	//index = -1 indicates the end of one vector
	_x[k].index = -1;
}