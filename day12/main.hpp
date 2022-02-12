
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

// split string
vector<const char*> c_split(const char* str, const char* tokens)
{
	vector<const char*> out;
	// extreme wonky c/c++ code
	char* cstr = new char(25);
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
