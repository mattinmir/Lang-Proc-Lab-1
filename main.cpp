#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream infile;
	infile.open(argv[1]);
	if (!infile.is_open())
	{
		cout << "Could not open input file" << endl;
		exit(EXIT_FAILURE);
	}

	ofstream outfile;
	outfile.open("clean.txt");
	if (!outfile.is_open())
	{
		cout << "Could not open output file" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	size_t block_comment_begin, block_comment_end, line_comment;
	bool in_block_comment = false;
	
	while (getline(infile, line))
	{
		if (in_block_comment)
		{
			block_comment_end = line.find("*/");
			if (block_comment_end != string::npos)
			{
				line.erase(0, block_comment_end + 2);
				in_block_comment = false;
			}
			else
				line.erase(0);
				
		}
		else
		{
			block_comment_begin = line.find("/*");
			if (block_comment_begin != string::npos)
			{
				block_comment_end = line.find("*/");
				if (block_comment_end != string::npos)
					line.erase(block_comment_begin, (block_comment_end + 2) - block_comment_begin);
				else
				{
					line.erase(block_comment_begin);
					in_block_comment = true;
				}
			}


			line_comment = line.find("//");
			if (line_comment != string::npos)
				line.erase(line_comment);
		}

		outfile << line << "\n";
	}

	infile.close();
	outfile.close();

	infile.open("clean.txt");
	if (!infile.is_open())
	{
		cout << "Could not open input file" << endl;
		exit(EXIT_FAILURE);
	}

	map<string, int> types = { ("char", 0), ("int", 0) };
	size_t _int, _char;
	while (getline(infile, line))
	{
		_int = line.find("int");
		if (_int != string::npos)
		{
			types["int"]++;
		}

		_char = line.find("char");
		if (_char != string::npos)
		{
			types["char"]++;
		}
	}
}