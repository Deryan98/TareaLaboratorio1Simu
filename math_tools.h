#include <vector>
#include "math.h"
#include "stdlib.h"
using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

//Vamos a crear operaciones para vectores y matrices

//Vector v recibe un vector por referencia ya que no quiero crear un vector nuevo
// int n es la longitud
void zeroes(Vector &v, int n){
    for(int i = 0; i < n; i++)
        v.push_back(0.0);
}

void zeroes(Matrix &M, int n){

  for(int i = 0; i < n ; i++){
    //Crea un vector que tiene una dimension n con valores 0.0 de inicializacion
    Vector row(n, 0.0); // con esto me estoy ahorrando un bucle for
    M.push_back(row);
  }

}

void copyVector(Vector v, Vector &copy){
  zeroes(copy,v.size());
  for(int i = 0; i < v.size() ; i++){
    copy.at(i) = v.at(i);
  }
}

void copyMatrix(Matrix A, Matrix &copy) {
  zeroes(copy, A.size());
  for(int i = 0; i < A.size() ; i++){
    for(int j = 0; j < A.at(0).size() ; j++){
      copy.at(i).at(j) = A.at(i).at(j);
    }
  }
}

void productMatrixVector(Matrix A, Vector v, Vector &R) {

  for(int fila = 0; fila < A.size() ; fila++){
    float cell = 0.0;
    for(int col= 0; col < v.size(); col++){
      cell += A.at(fila).at(col) * v.at(col);
    }
    R.at(fila) += cell;
  }

}

void productRealMatrix(float real,Matrix M,Matrix &R){
    zeroes(R,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            R.at(i).at(j) = real*M.at(i).at(j);
}

float calculateMember(int i,int j,int r,Matrix A,Matrix B){
    float member = 0;
    for(int k=0;k<r;k++)
        member += A.at(i).at(k)*B.at(k).at(j);
    return member;
}

Matrix productMatrixMatrix(Matrix A,Matrix B,int n,int r,int m){
    Matrix R;

    zeroes(R,n);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            R.at(i).at(j) = calculateMember(i,j,r,A,B);

    return R;
}

void getMinor(Matrix &M,int i, int j){
    M.erase(M.begin()+i); 
    for(int i=0;i<M.size();i++)
        M.at(i).erase(M.at(i).begin()+j);
}

float determinant(Matrix M){
    if(M.size() == 1) return M.at(0).at(0);
    else{
        float det=0.0;
        for(int i=0;i<M.at(0).size();i++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,0,i);
            det += pow(-1,i)*M.at(0).at(i)*determinant(minor);
        }
        return det;
    }
}

Vector sumVector(Vector A,Vector B,int n){
    Vector R;

    zeroes(R,n);
    for(int i=0;i<n;i++)
        R.at(i) = A.at(i)+B.at(i);

    return R;
}

Matrix sumMatrix(Matrix A,Matrix B,int n,int m){
    Matrix R;

    zeroes(R,n);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            R.at(i).at(j) = A.at(i).at(j)+B.at(i).at(j);

    return R;
}

void cofactors(Matrix M, Matrix &Cof){
    zeroes(Cof,M.size());
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M.at(0).size();j++){
            Matrix minor;
            copyMatrix(M,minor);
            getMinor(minor,i,j);
            Cof.at(i).at(j) = pow(-1,i+j)*determinant(minor);
        }
    }
}

void transpose(Matrix M, Matrix &T){
    zeroes(T,M.size());
    for(int i=0;i<M.size();i++)
        for(int j=0;j<M.at(0).size();j++)
            T.at(j).at(i) = M.at(i).at(j);
}

void attached(Matrix M, Matrix &A){
  Matrix Cofactors;
  cofactors(M, Cofactors);
  transpose(Cofactors, A);
}

void inverse(Matrix M, Matrix &I){
  
  float det = determinant(M);
  //Evaluamos si el determinante es cero
  if(det == 0)
    //Si se cumple terminamos el programa
    exit(EXIT_FAILURE);
  
  //creamos la Adjunta
  Matrix Adjunta;
  //Mandamos a sacar la adjunta
  attached(M, Adjunta);
  //obtenemos el inverso del determinante
  float real = 1/det;
  //Multiplicamos escalar por matriz
  productRealMatrix(real,Adjunta,I);

}

