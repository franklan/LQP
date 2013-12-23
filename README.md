# Local Quantized Pattern #


This is an implementation for Local Quantized Pattern feature which is very popular on the research of face recognition and object recognition. 

## What is LQP ##
LQP is a generalization of local pattern features(LBP) that makes use of vector quantization and lookup table to let local pattern features have many more pixels and/or quantization levels without sacrificing simplicity and computational efficiency. More information about LQP, please refer to  

[Visual Recognition using Local Quantized Patterns](http://hal.archives-ouvertes.fr/docs/00/69/56/27/PDF/lqp-tr-hal.pdf "Visual Recognition using Local Quantized Patterns")

[Face Recognition using Local Quantized Patterns](https://jurie.users.greyc.fr/papers/12_bmvc-12_faces.pdf "Face Recognition using Local Quantized Patterns")

The project is based on the [Opencv ](http://opencv.org/ "Opencv") library when dealing with the pixels.



## Usage ##

Step 1: Generate Codebook of LQP based on the training data

    bin/extractLQP jpglist codebookFile ClucenterFile -g

Step 2: Cluster

    bin/KMeans codebookFile midResult ClucenterFile

step 3: Extract LQP Feature，LQP_feature is the output file.

    bin/extractLQP JpgList LQP_feature ClucenterFile -e

## Discussion ##

Any bugs, feel free to contact me, or you have some ideas about improving the result. I am very grateful you have any recommendations.