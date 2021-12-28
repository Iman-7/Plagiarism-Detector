# Simple Plagiarism Detection Utility using String Matching Algorithms

#### Introduction

	In this project, we are required to detect the plagiarism in a specific pattern from a given
document, through different approaches. The input will be a determined number of patterns,
with existing documents which can include some sentences from the pattern or not. The project
can execute the following tasks: detecting the plagiarized patterns, highlighting the documents
that the plagiarism takes place from, and calculating the plagiarism percentage of the pattern
from each document and the total percentage of plagiarism. The project is executing its function
using four different algorithms to compare between the time complexity of each algorithm and
choose the better one. The project’s performance is determined by the accuracy of the
plagiarism percentage detected on a specific pattern on each document besides the total
percentage.

#### Problem Definition

	The project depends on four main algorithms to detect the string matching between the pattern
and the document: Hamming Distance, Rabin Karp Algorithm, KMP Algorithm, and Boyer-Moore
Algorithm. Generally, we take the input pattern as a set of sentences which are separated by
dots, while taking the input documents as a set of strings; each string stores one of the
documents as a whole. The strategy is to loop on every sentence in the pattern and detect if it
was plagiarized or not by looping again on every document in our database. At this point, the
output can be represented by the following style: (assuming we have 2 patterns, each pattern
has 3 sentences, and we have 3 documents)

| | Document 1 | Document 2 | Document 3 |
| ------ |------ |------ |------ |
| Pattern 1 | (true, flase, flase) | (false, flase, flase) | (true, true, flase) |
| Pattern 2 | (false, flase, flase) | (true, true, true) | (false, flase, true) |

In the table above, we can see that when Pattern 1 is compared with Document 1, the output is
(true, false, false), which means that the 1st sentence in the pattern is detected as plagiarism
while the two remaining sentences are not. Consequently, we apply several approaches to
improve the output and increase the project efficiency.

#### User Guide

How to use the palagrisim detection utility:

	1. You need to change the paths of the files in both taking_input_text() function and taking_input_pattern() function to the path of the folder that contains your files.
	2. You need to adjust the value of the global variable num_text_files to the number of text files you want.  
	3. You need to adjust the value of the global variable num_pat_files to the number of pattern files you want. 
	4. You need to update the names of the pattern documents in the pat_files[] array and update the names of the text files in the text_files[] array. 
	5. Run the algorithm to enjoy the output. 

