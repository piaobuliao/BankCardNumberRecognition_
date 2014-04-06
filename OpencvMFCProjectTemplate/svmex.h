#include <vector>
//#include "ParkingLot.h"
#include "svm.h"



//convert vector to struct svm_node array format
//NOTICE: the function assumes memory of _x has been allocated.
void ConvertToLibSVMFormat(std::vector<int>& features,std::vector<int>& missing_feature_flag, struct svm_node* _x);

void ConvertToLibSVMFormat(double* features, bool* missing_feature_flag, int count, struct svm_node* _x);

void ConvertToLibSVMFormat(std::vector<float>& features, int count, struct svm_node* _x);