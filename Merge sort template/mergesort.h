

template <typename T> void Merge(std::vector<T>& data, unsigned int firstToSort, unsigned int midPoint,  unsigned int lastToSort){
    int mergedSize = lastToSort - firstToSort + 1; 
    int mergePos = 0;
    int leftPos = firstToSort;  
    int rightPos = midPoint + 1;
    std::vector<T> tempMerge(mergedSize);

    while (leftPos <= midPoint && rightPos <= lastToSort) {
      if (data.at(leftPos) < data.at(rightPos)) {
         tempMerge.at(mergePos) = data.at(leftPos);
         leftPos++;
      }
      else {
         tempMerge.at(mergePos) = data.at(rightPos);
         rightPos++;
         
      }
      mergePos++;
   }
   
   while (leftPos <= midPoint) {
      tempMerge.at(mergePos) = data.at(leftPos);
      leftPos++;
      mergePos++;
   }

   while (rightPos <= lastToSort) {
      tempMerge.at(mergePos) = data.at(rightPos);
      rightPos++;
      mergePos++;
   }
   
   for (mergePos = 0; mergePos < mergedSize; mergePos++) {
      data.at(firstToSort + mergePos) = tempMerge.at(mergePos);
   }

} 

template <typename T> void mergeSort(std::vector<T>& data, unsigned int firstToSort, unsigned int lastToSort){
    int midPoint;
   
    if (firstToSort < lastToSort) {
      midPoint = (firstToSort + lastToSort) / 2;  

      mergeSort(data, firstToSort, midPoint);
      mergeSort(data, midPoint + 1, lastToSort);
      
      Merge(data, firstToSort, midPoint, lastToSort);
   }
}