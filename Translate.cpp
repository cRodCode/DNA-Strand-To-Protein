// Module:      Translate
// Author:      Carlos Rodriguez
// Date:        8/31/2022
// Purpose:     Take in DNA strand txt file translate it to tRNA
//              translate tRNA to proteins

#include "framework.h"
#include "DNAStrandToProteinGUI.h"

vector<string> dnaTriplet;				// hold dnaTriplets
vector<string> tRnaTriplet;				// hold tRnaTriplets
vector<string> proteins;				// hold proteins

void Translate::readFile(string fileName)
{
    ifstream fileInput;                     // file handler
    string dnaData = "";                    // hold our dna string

    try {
        fileInput.open(fileName);           // try to open file
        string temp = "";
        if (!fileInput)
            throw runtime_error("File not found");
        if (fileInput.is_open())
        {
            while (fileInput.good())
            {
                getline(fileInput, dnaData);    // get line of string

                for (int x = 0; x < dnaData.length() / 3; x++)                                    // loops the length of string divided by 3 
                {
                    // grab 3 chars
                    temp += dnaData[x * 3];
                    temp += dnaData[x * 3 + 1];
                    temp += dnaData[x * 3 + 2];

                    dnaTriplet.push_back(temp);                                                     // adds a set of three chars to vector list
                    temp = "";                                                                      // clear temp
                }
            }
            fileInput.close();
        }

    }
    catch (exception e)
    {
        MessageBox(NULL,
            TEXT("Unable to open input file"),
            TEXT("File Open error"),
            MB_ICONEXCLAMATION);
        dnaTriplet.clear();
        tRnaTriplet.clear();
        proteins.clear();
        
    }
    
}

void Translate::toTrna()
{
    string temp = "";
    try {
        for (int x = 0; x < dnaTriplet.size(); x++)
        {
            for (int i = 0; i <= 2; i++)
            {
                switch (int(dnaTriplet[x].at(i)) - 65)
                {
                case 0:                         // A
                    temp += dnaTriplet[x].at(i);
                    break;
                case 2:                         // C
                    temp += dnaTriplet[x].at(i);
                    break;
                case 6:                         // G
                    temp += dnaTriplet[x].at(i);
                    break;
                case 19:                        // T
                    temp += 'U';
                    break;
                default:
                    MessageBox(NULL,
                        TEXT("Invalid DNA strand found try again"),
                        TEXT("File read error"),
                        MB_ICONEXCLAMATION);
                    throw runtime_error("Invalid input");
                    break;
                }
            }
            tRnaTriplet.push_back(temp);
            temp = "";
        }
    }
    catch (exception e)
    {
        Translate::clear();
    }

}

void Translate::toProtein()
{
    for (int x = 0; x < tRnaTriplet.size(); x++)
    {
        if (tRnaTriplet[x] == "UUU" || tRnaTriplet[x] == "UUC")
        {
            proteins.push_back("Phenylalanine");
        }
        else if (tRnaTriplet[x] == "UUA" || tRnaTriplet[x] == "UUG" || tRnaTriplet[x] == "CUU" || tRnaTriplet[x] == "CUC" || tRnaTriplet[x] == "CUA" || tRnaTriplet[x] == "CUG")
        {
            proteins.push_back("Leucine");
        }
        else if (tRnaTriplet[x] == "UCU" || tRnaTriplet[x] == "UCC" || tRnaTriplet[x] == "UCA" || tRnaTriplet[x] == "UCG")
        {
            proteins.push_back("Serine");
        }
        else if (tRnaTriplet[x] == "CCU" || tRnaTriplet[x] == "CCC" || tRnaTriplet[x] == "CCA" || tRnaTriplet[x] == "CCG")
        {
            proteins.push_back("Proline");
        }
        else if (tRnaTriplet[x] == "UAU" || tRnaTriplet[x] == "UAC")
        {
            proteins.push_back("Tyrosine");
        }
        else if (tRnaTriplet[x] == "UAA" || tRnaTriplet[x] == "UAG" || tRnaTriplet[x] == "UGA")
        {
            proteins.push_back("STOP");
        }
        else if (tRnaTriplet[x] == "UGU" || tRnaTriplet[x] == "UGC")
        {
            proteins.push_back("Cysteine");
        }
        else if (tRnaTriplet[x] == "UGG")
        {
            proteins.push_back("Tryptophan");
        }
        else if (tRnaTriplet[x] == "CAU" || tRnaTriplet[x] == "CAC")
        {
            proteins.push_back("Histidine");
        }
        else if (tRnaTriplet[x] == "CAA" || tRnaTriplet[x] == "CAG")
        {
            proteins.push_back("Glutamine");
        }
        else if (tRnaTriplet[x] == "CGU" || tRnaTriplet[x] == "CGC" || tRnaTriplet[x] == "CGA" || tRnaTriplet[x] == "CGG")
        {
            proteins.push_back("Arginine");
        }
        else if (tRnaTriplet[x] == "AUU" || tRnaTriplet[x] == "AUC" || tRnaTriplet[x] == "AUA")
        {
            proteins.push_back("Isoleucine");
        }
        else if (tRnaTriplet[x] == "AUG")
        {
            proteins.push_back("START");
        }
        else if (tRnaTriplet[x] == "ACU" || tRnaTriplet[x] == "ACC" || tRnaTriplet[x] == "ACA" || tRnaTriplet[x] == "ACG")
        {
            proteins.push_back("Threonine");
        }
        else if (tRnaTriplet[x] == "AAU" || tRnaTriplet[x] == "AAC")
        {
            proteins.push_back("Asparagine");
        }
        else if (tRnaTriplet[x] == "AAA" || tRnaTriplet[x] == "AAG")
        {
            proteins.push_back("Lysine");
        }
        else if (tRnaTriplet[x] == "AGU" || tRnaTriplet[x] == "AGC")
        {
            proteins.push_back("Serine");
        }
        else if (tRnaTriplet[x] == "AGA" || tRnaTriplet[x] == "AGG")
        {
            proteins.push_back("Arginine");
        }
        else if (tRnaTriplet[x] == "GUU" || tRnaTriplet[x] == "GUC" || tRnaTriplet[x] == "GUA" || tRnaTriplet[x] == "GUG")
        {
            proteins.push_back("Valine");
        }
        else if (tRnaTriplet[x] == "GCU" || tRnaTriplet[x] == "GCC" || tRnaTriplet[x] == "GCA" || tRnaTriplet[x] == "GCG")
        {
            proteins.push_back("Alanine");
        }
        else if (tRnaTriplet[x] == "GAU" || tRnaTriplet[x] == "GAC")
        {
            proteins.push_back("Aspartate");
        }
        else if (tRnaTriplet[x] == "GAA" || tRnaTriplet[x] == "GAG")
        {
            proteins.push_back("Glutamate");
        }
        else if (tRnaTriplet[x] == "GGU" || tRnaTriplet[x] == "GGC" || tRnaTriplet[x] == "GGA" || tRnaTriplet[x] == "GGG")
        {
            proteins.push_back("Glycine");
        }
    }
}

void Translate::outputFile(string Output)
{
    ofstream outputFile;                        // file handler

    try {
        outputFile.open(Output, ios::out, ios::trunc);

        if (!outputFile)
            throw runtime_error("File not found");
        if (outputFile.is_open())
        {
            for (int x = 0; x < proteins.size(); x++)
            {
                outputFile << "| " << to_string(x) << " |" << tRnaTriplet[x];
            }
            outputFile << endl;
            for (int x = 0; x < proteins.size(); x++)
            {
                outputFile << "| " << to_string(x) << " |" << proteins[x];
            }
        }
    }
    catch (exception e)
    {
        MessageBox(NULL,
            TEXT("Couldn't export file!"),
            TEXT("File write error"),
            MB_ICONEXCLAMATION);
    }
    outputFile.close();
    dnaTriplet.clear();				
    tRnaTriplet.clear();				
    proteins.clear();
}

void Translate::clear()
{
    dnaTriplet.clear();
    tRnaTriplet.clear();
    proteins.clear();
}
