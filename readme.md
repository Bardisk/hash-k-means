# Hash-k-means

This is a tool to cluster dhash values of a given image group using k-means.

We use the hamming distance as the measure of two hash values' distance.

This tool will get the list of hash values from the standard input, and give the list of cluster centers to the standard output. Use `-c CLUSTERS` to specify the number of clusters and `-t EPOCHS` to specify the number of epoches the tool will run.