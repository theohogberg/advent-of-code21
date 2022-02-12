
// fetch input
vector<string> fetch_input(string file)
{
	vector<string> out;
	ifstream inpstream("input");
	if (inpstream.is_open())
	{
		string line;
		// getline is non-zero
		while (getline(inpstream, line))
		{
			// push to vector
			out.push_back(line);
		}
	}

	return out;
}

// split string c++
vector<string> cpp_split(string str, string delim)
{
	size_t pos = 0;
	vector<string> out;
	string token;
	
	while ((pos = str.find(delim)) != string::npos)
	{
		token = str.substr(0, pos);
		out.push_back(token);
		str.erase(0, pos + delim.length());
	}
	
	// add the last part
	if (!str.empty())
		out.push_back(str);
		
	return out;
}

// split string
vector<const char*> c_split(const char* str, const char* tokens)
{
	vector<const char*> out;
	// extreme wonky c/c++ code
	char* cstr = new char[strlen(str) + 1];
	strcpy(cstr, str);
	char* pch = strtok(cstr, tokens);
	while (pch != NULL)
	{
		out.push_back(pch);
		pch = strtok(NULL, tokens);
	}

	return out;
}

// find in vector
template <typename T>
int find_in_vector(T elem, vector<T> v)
{
	auto it = find(v.begin(), v.end(), elem);
	if (it != v.end())
		return 1;
	else
		return 0;
}

// print vector
template <typename T>
void print_vector(string msg, vector<T> v)
{
	cout << msg << endl;
	for (const auto& e : v)
	{
		cout << e << endl;
	}
}
