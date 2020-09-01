  double dotpr3 (vector1, vector2)
    double vector1[3],
           vector2[3];
/*
%%  Dot product of two 3-dimensional vectors.
---
 
LANGUAGE:  C
ENVIRONMENT:  Any standard C.
TESTED:  6 Jan 86, D. King -- A routine which uses this works properly,
                   so presumably this works properly.
 
::  vector  dot  product  multiply
 
++$  Audit Trail
    1.0   86jan07   D. King   Initial Submission.
--$
-*/
#define version 1.0
 
{
    register int i;
    register double *v1 = vector1,
                    *v2 = vector2;
    double sum = 0.0;
 
    for (i = 0; i < 3; i++)
        sum += *v1++ * *v2++;
    return (sum);
}
