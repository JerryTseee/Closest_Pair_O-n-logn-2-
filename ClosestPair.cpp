/*
We are given an array of n points in the plane, and the problem is to find out the closest pair of points in the array.

Algorithm:
1. input array is sorted according to x-coordinates.
2. Divide the array into two equal parts.
3. Recursively find the smallest distances in both subarrays.
4. Take the minimum of two smallest distances d.
5. Create an array strip[] that stores all points which are at most d distance away from the middle line dividing the two sets.(this step shows that we need to consider the pair that intersects the middle line)
6. Find the smallest distance in strip[].
7. Return the smallest of two distances.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cfloat>
using namespace std;

// a class represent a point in 2D plane
class point
{
    public:
    int x;
    int y;
};

//compare x value, then sort function
int compareX(const void* a, const void* b)
{
    point *p1 = (point *)a, *p2 = (point *)b;
    return (p1->x - p2->x);
}

//compare y value, then sort function
int compareY(const void* a, const void* b)
{
    point *p1 = (point *)a, *p2 = (point *)b;
    return (p1->y - p2->y);
}

//function to find the distance between two points
float dist(point p1, point p2)
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

//using brute force to return the smallest distance between two points
float bruteForce(point P[], int n)
{
    float min = FLT_MAX; //initialize the minimum distance
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);// updare the minimum distance
        }
    }
    return min;
}

//find minimum of two float values
float min(float x, float y)
{
    return (x < y)? x : y;
}

// function to find the closest points of the strip[]
float stripClosest(point strip[], int size, float d)
{
    float min = d; //initialize the minimum distance
    qsort(strip, size, sizeof(point), compareY); //sort the strip[] array according to y-coordinates
    for(int i = 0; i < size; i++)
    {
        for(int j = i+1; j < size && (strip[j].y - strip[i].y) < min; j++)
        {
            if(dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]); //update the minimum distance
        }
    }
    return min;
}



//recursive function to find the smallest distance->main logic here!!!
float closestUtil(point P[], int n)
{
    if(n <= 3)
        return bruteForce(P, n); //if there are less than 3 points, use brute force
    int mid = n/2; //find the middle point
    point midPoint = P[mid]; //get the middle point
    float dl = closestUtil(P, mid); 
    float dr = closestUtil(P + mid, n - mid);
    float d = min(dl, dr); //find the minimum of two distances
    point strip[n]; 
    int j = 0; 
    for (int i = 0; i < n; i++) 
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i];//fill the strip
            j++; 
 
    return min(d, stripClosest(strip, j, d) );//here is the final results!!!
}

int main(){

    point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}}; //initialize the points
    int n = sizeof(P)/sizeof(P[0]);
    //using quick sort to sort first (this is the first step)
    qsort(P, n, sizeof(point), compareX);
    cout<<"The smallest distance is: "<<closestUtil(P, n)<<endl;
}