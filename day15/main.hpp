// fetch input
vector<string> fetch_input(string file)
{
    vector<string> out;
    ifstream inpstream(file);
    if (inpstream.is_open())
    {
        string line;
        while (getline(inpstream, line))
        {
            out.push_back(line);
        }
        inpstream.close();
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