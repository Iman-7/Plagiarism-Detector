#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>
# define NO_OF_CHARS 256

using namespace std;

int num_text_files = 5;
int num_pat_files = 2;
vector <string> pattern;
vector <vector<string>> text(num_text_files);
int pattern_char_total = 0;
vector <int> counter(4, 0);

// should we put in mind the captalization????? DONE

//BF algorithm for string matching - complexity O(nm)
bool BF(string pattern, string text, int row) {
	int n = text.length();
	int m = pattern.length();


	for (int i = 0; i <= n - m; i++) { // we faced a problem when the pattern and the text are the same 
														// i.e. n = m, e.g. ptrn ="Iman", txt = "Iman", so i added this condition
		int D = 0; int j = 0;
		for (j = 0; j < m; j++) {
			if (text[i + j] != pattern[j]) {
				D++; //increment no. of mis-matches
				counter[0]++;
			}
			//cout << "hamming distance is: " << D << endl;
		}
		if (D == 0) {
			
			cout << "pattern is found in the following text in row: " << row <<" at index: " << i + j - m << endl;
			return true;
		}
	}
	return false;
}


bool RK(string pattern, string text, int row)
{
	int prime = 101;   //the larger the prime number, the smaller the chance of collisions
	int size_p = pattern.size();
	int size_t = text.size();
	int i, j;
	int hash_p = 0; // hash value for pattern
	int hash_t = 0; // hash value for text
	int h = 1;

	// h= d^(m-1)
	for (i = 0; i < size_p - 1; i++)
		h = (h * 256) % prime;

	//calculate hash values
	for (i = 0; i < size_p; i++)
	{
		hash_p = (256 * hash_p + pattern[i]) % prime;
		hash_t = (256 * hash_t + text[i]) % prime;
	}

	// Sliding
	for (i = 0; i <= size_t - size_p; i++)
	{

		//if the hash values of the string and text match, then compare characters
		
		counter[1]++;
		if (hash_p == hash_t)
		{

			for (j = 0; j < size_p; j++)
			{
				counter[1]++;
				if (text[i + j] != pattern[j])
					break;
			}

			// if hash_p == hash_t and pattern[0...M-1] = text[i, ..., M-1]
			if (j == size_p) {
					cout << "Pattern found in the following text in row: " << row << " at index " << i << endl;
				return true;
			}
		}

		//calculate the hash value of the next window from the previous one
		if (i < size_t - size_p)
		{
			hash_t = (256 * (hash_t - text[i] * h) + text[i + size_p]) % prime;

			//in case hash_t is negative, we get its positive
			if (hash_t < 0)
				hash_t = (hash_t + prime);
		}

	}
	return false;
}

//KMP
void computeLPSArray(string pat, int M, vector <int> lps)
{

	int len = 0;

	lps[0] = 0;


	int i = 1;
	while (i < M) {
		counter[2]++;
		if (pat[i] == pat[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else
		{

			if (len != 0) {
				len = lps[len - 1];


			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}


bool KMPSearch(string pat, string txt, int row)
{
	int M = pat.size();
	int N = txt.size();

	// create lps[] that will hold the longest prefix suffix
	// values for pattern
	vector <int> lps(M);

	// Preprocess the pattern (calculate lps[] array)
	computeLPSArray(pat, M, lps);

	int i = 0; // index for txt[]
	int j = 0; // index for pat[]
	while (i < N) {
		counter[2]++;
		if (pat[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {

				cout << "Found pattern in the following text at index in row " << row <<" at index : " << i - j;
				cout << endl;
			
			j = lps[j - 1];
			return true;
		}
		// mismatch after j matches
		else if (i < N && counter[2]++ && pat[j] != txt[i]) {
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = lps[j - 1];
			//return true;}
			else
				i = i + 1;
			// return false;}

		}
	}
	return false;
}

//Boyer Moore algorithm for string matching - complexity O(nm)
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS])
{
	int i;

	// Initialize all occurrences as -1
	for (i = 0; i < NO_OF_CHARS; i++)
		badchar[i] = -1;

	// Fill the actual value of last occurrence
	// of a character
	for (i = 0; i < size; i++)
		badchar[(int)str[i]] = i;
}

bool BoyerMoore(string pat, string txt, int row)
{
	int m = pat.size();
	int n = txt.size();

	int badchar[NO_OF_CHARS];

	badCharHeuristic(pat, m, badchar);

	int s = 0;
	while (s <= (n - m))
	{
		int j = m - 1;
		

		while (j >= 0 && counter[3]++ && pat[j] == txt[s + j])
			j--;

		if (j < 0)
		{
				cout << "pattern found in the following text in row " << row <<" at index: " << s << endl;
			return true;
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
		}

		else {
			s += max(1, j - badchar[txt[s + j]]);
		}
	}
	return false;

}

string make_lowercase(string in)
{
	string out;

	transform(in.begin(), in.end(), back_inserter(out), tolower);

	return out;
}

void taking_input_text(string txt_file_name, int idx) {
	ifstream file_text("C:/Users/Dell/Desktop/Spring 2021/Algorithms/Project/" + txt_file_name + ".txt");
	string line;

	if (!file_text.is_open())
	{
		cout << "error opening the file" << endl;
		return;
	}
	else
	{
		//cout << "file: " << idx << endl;
		int i = 0;
		while (getline(file_text, line, '\n')) {
			stringstream data(line);
			while (getline(data, line, '.')) {
				text[idx].push_back(line);


				text[idx][i] = make_lowercase(text[idx][i]);

				
				//cout << text[idx][i] << endl;
				i++;
			}

		}
	}

		//cout << text[idx];
		//cout << text[idx].size();
		file_text.close();

	

}

void taking_input_pattern(string pat_file_name) {

	ifstream file_pattern("C:/Users/Dell/Desktop/Spring 2021/Algorithms/Project/" + pat_file_name + ".txt");

	string line;

	if (!file_pattern.is_open())
	{
		cout << "error opening the file" << endl;
		return;
	}
	else
	{
		int i = 0;
		while (getline(file_pattern, line, '\n')) {
			stringstream data(line);
			while (getline(data, line, '.'))
			{
				pattern.push_back(line);
				pattern_char_total += pattern[i].size();

				pattern[i] = make_lowercase(pattern[i]);

				//cout << pattern[i] << endl;
				i++;
			}
		}
		//cout << pattern.size();
		file_pattern.close();

	}

}

void test_algorithms(int algorithm_num) {

	string pat_files[] = { "pattern_0", "pattern_1"};

	for (int p = 0; p < num_pat_files; p++) {
		taking_input_pattern(pat_files[p]);
		cout << "pattern (" << p << ") situation: \n";
		vector <bool> palagirized_or_not(pattern.size(), false);
		vector <double> palagrized_length(num_text_files);
		double palagrisim_percent = 0;

		for (int i = 0; i < num_text_files; i++) {
			double start_time = clock();
			for (int j = 0; j < pattern.size(); j++) {
				for (int k = 0; k < text[i].size(); k++) {
					switch (algorithm_num) {
					case 1:
						if (BF(pattern[j], text[i][k],k))
						{
							//cout << "true \n";
							palagrized_length[i] += pattern[j].size();
							palagirized_or_not[j] = true;
						}
						break;
					case 2:
						if (RK(pattern[j], text[i][k],k))
						{
							palagrized_length[i] += pattern[j].size();
							palagirized_or_not[j] = true;
						}
						break;
					case 3:
						if (KMPSearch(pattern[j], text[i][k],k))
						{
							palagrized_length[i] += pattern[j].size();
							palagirized_or_not[j] = true;
						}
						break;
					case 4:
						if (BoyerMoore(pattern[j], text[i][k],k))
						{
							palagrized_length[i] += pattern[j].size();
							palagirized_or_not[j] = true;
						}
						break;
					default:
						break;
					}
				}
			}
			double end_time = clock();
			double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
			palagrisim_percent = (palagrized_length[i] / pattern_char_total) * 100;
			cout << "palagrisim from text number " << i << " is: " << setprecision(4) << palagrisim_percent << " % \n";

			//for (int i = 0; i < counter.size(); i++) counter[i] = 0;

		}

		double total_percent = 0;
		for (int i = 0; i < pattern.size(); i++)
			if (palagirized_or_not[i])
				total_percent += (double(pattern[i].size()) / double(pattern_char_total));
		total_percent *= 100;
		cout << "Total plagiarism percentage = " << total_percent << " %" << endl;
		if (total_percent > 50)
			cout << "The palagrism percentage is not acceptable!! This is academic dishoensty!!\n";
		else
			cout << "Accepted percentage!! no palagrism detected!!\n";
		cout << endl << endl;

		pattern.resize(0);
		pattern_char_total = 0;
	}
}

int main() {

	string text_files[] = { "text_0", "text_1", "text_2", "text_3", "text_4" };
	for (int i = 0; i < num_text_files; i++) {
		taking_input_text(text_files[i], i);
	}

	//n: text size, m: pattern size
	//o(mn) - best case o(m)
	cout << "testing of brute force (bf) algorithm: \n";
	test_algorithms(1);
	cout << endl;
	
	////O(mn) - Best and average-case O(m + n)
	cout << "Testing of Rabin Karp (RK) Algorithm: \n";
	test_algorithms(1);
	cout << endl;

	//O(m+n) - Best case O(m)
	cout << "Testing of KMP Algorithm: \n";
	test_algorithms(3);
	cout << endl;

	//O(mn) - O(m)
	cout << "Testing of Boyer Moore Algorithm: \n";
	test_algorithms(4);
	cout << endl;

	return 0;
}