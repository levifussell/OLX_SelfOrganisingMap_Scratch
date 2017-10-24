# OLX_SelfOrganisingMap_Scratch
An upload of work done for the OLX 2017 competition on hackerrank.com. I am working on formalising the concepts into a SOM library. For now the gist is to use SOMs as a form of recommendation system for adverts.

Background:
1. Self-Organising Maps: https://www.wikiwand.com/en/Self-organizing_map
2. Jaccard Distance: https://www.wikiwand.com/en/Jaccard_index

# Brief Outline of Files
## 1.) DataAnalysis.ipynb
Preprocessing steps to understand the data and possible cleaning. Other than getting a feel for the data, the most important step was utilising the Pareto distribution to decrease the dataset by five-fold.
Here I also started testing out my first SOM implementation on the data.

## 2.) KohonenMap.ipynb
More functional implementation of SOM and started testing some metrics. There are some notes on various hyperparams, but alot of this was done on scratch paper and isn't on the notebook (sadly).
Note: I copied a large portion of the previous notebook to this one so that the data pre-processing was done for me, hence the random data cells.

## 3.) KohonenMapWithCategory.ipynb
Same SOM as before, but we adjust the implementation to make use of weights that emphasise categories in the ads. Results are much better.

## 4.) JaccardDistance.ipynb
Baseline for a recommendation system. Note the poor performance of this model emphasises the difficulty of this dataset.

## 5.) main.cpp
Data querying and processing.

## 6.) final_user_messages_test.csv
Output of models (this could be Jaccard or SOM depending on which one I ran last).

# Where's the data?
The dataset was too large to upload (github 100MB limit) therefore it has to be downloaded here:

https://www.hackerrank.com/contests/code-and-the-curious/challenges

Trained models have not been uploaded either.
