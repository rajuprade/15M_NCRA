#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "jnic.h"

JNIEXPORT jstring JNICALL Java_jnic_sayHello
  (JNIEnv *env, jobject thisobject, jstring js)

{

	return js;
}

