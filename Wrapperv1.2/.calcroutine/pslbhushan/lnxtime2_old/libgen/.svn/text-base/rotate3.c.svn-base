  void rotate3 (out_vector, matrix, in_vector)
    double out_vector[3],              /*  output product-vector     */
           matrix[3][3],               /*  input matrix              */
           in_vector[3];               /*  input vector              */
/*
%%  Multiply a vector by a rotation matrix.
 
      Multiplies a 3 x 3 matrix by a 3-component (column) vector to
      obtain another 3-component (column) vector.  In matrix notation:
             (product_vector) = (matrix) * (input_vector).
 
      Typical use would be co-ordinate transformation.
---
 
LANGUAGE:  C
ENVIRONMENT:  Any Standard C
TESTED:  6 Jan 86, D. King.  Input was an assymetric matrix with all non-zero
                   elements, and a couple of different vectors.
EXTERNAL REFERENCES:
    EXTERNAL FUNCTIONS in VLBCLIB:
        dotpr3
 
::  matrix  multiply  vector  rotate
 
++$  Audit Trail
    1.0   86jan07   D. King   Initial Submission.
--$
 
-*/
 
#define version 1.0
 
{
    int i;
    double dotpr3();
 
    for (i = 0; i < 3; i++)
        out_vector[i] = dotpr3(matrix[i], in_vector);
}
