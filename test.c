/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/26/2014 15:36:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ravish Mishra (), ravish.mishra@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
int getInvCount(int arr[], int n)
{
  int inv_count = 0;
  int i, j;
 
  for(i = 0; i < n - 1; i++)
    for(j = i+1; j < n; j++)
      if(arr[i] > arr[j])
        inv_count++;
 
  return inv_count;
}
 
/* Driver progra to test above functions */
int main(int argv, char** args)
{
  int arr[] = {10,9,8,7,6,5,4,3,2,1};
  printf(" Number of inversions are %d \n", getInvCount(arr, 10));
  getchar();
  return 0;
}

