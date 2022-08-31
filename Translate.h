// Project:     DNAStrandToProteinGUI
// Author:      Carlos Rodriguez
// Date:        8/31/2022
// Purpose:     Header file for translate

#pragma once
class Translate
{
public:
	void readFile(string);                  // read file and place into vector into sets of three
	void toTrna();							// convert dna to tRNA
	void toProtein();						// convert tRNA to a protein
	void outputFile(string);                // export to file
	void clear();

private:


};

