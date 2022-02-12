
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

// print vector
template <typename T>
void print_vector(string msg, vector<T> v)
{
	cout << msg << endl;
	for (const auto& e : v)
	{
			cout << e << endl;
	}
	cout << endl;
}
