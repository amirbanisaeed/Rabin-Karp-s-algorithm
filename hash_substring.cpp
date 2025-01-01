#include <iostream>
#include <string>
#include <vector>

using std::string;
using namespace std;
typedef unsigned long long ull;

struct Data
{
    string pattern, text;
};

size_t Polyhash_func(const string& s)
{
    int bucket_count = 12;
    static size_t multiplier = 1;
    static size_t prime = 1000000007;
    ull hash = 0;
    for (long long int i = static_cast<int>(s.size()) - 1; i >= 0; --i)
        hash = (((hash * multiplier + s[i]) % prime) + prime) % prime;
    return hash;
}

bool match(const std::string& s1, const std::string& s2)
{
    for (int i = 0; i < s2.size(); i++)
    {
        if (s1[i] != s2[i])
            return false;
    }
    return true;
}

vector<size_t> PrecomputeHashes(const Data& input)
{
    const string& s = input.pattern, t = input.text;
    static size_t multiplier = 1;
    static size_t prime = 1000000007;
    ull sizeOfT = input.text.size();
    ull sizeOfP = input.pattern.size();
    vector<size_t> H(sizeOfT - sizeOfP + 1);
    H[sizeOfT - sizeOfP] = Polyhash_func(t.substr(sizeOfT - sizeOfP, sizeOfP));
    // H[sizeOfT - sizeOfP - 1] = Polyhash_func(t.substr(sizeOfT - sizeOfP - 1, sizeOfT - 2));

     // cout << H[sizeOfT - sizeOfP - 1] << endl;
    ull y = 1;

    for (long long int i = 0; i < sizeOfP; i++)
    {
        y = (((y * multiplier) % prime) + prime) % prime;
    }

    //cout << "Begin: " << endl;
    for (long long int i = sizeOfT - sizeOfP - 1; i >= 0; --i)
    {
        H[i] = (((multiplier * H[i + 1] + t[i] - (y * t[i + sizeOfP])) % prime) + prime) % prime;
        //    cout << H[i] << endl;
    }

    return H;
}

Data read_input()
{
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<ull>& output)
{
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}
/*
std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}
*/

std::vector<ull> get_occurrences(const Data& input)
{
    const string& s = input.pattern, t = input.text;
    size_t hashPattern = Polyhash_func(s);

    //  cout << "HashPattern: "<<hashPattern << endl;
    vector<size_t> hashText(t.size());

    hashText = PrecomputeHashes(input);

    //    for (size_t i = 0; i < hashText.size(); i++)
     //   {
     //       cout << "hash " << i << " " << hashText[i] << endl;
      //  }

    std::vector<ull> ans;

    for (size_t i = 0; i <= hashText.size(); i++)
    {
        //   cout << "HOO" << endl;
        if (hashText[i] == hashPattern)
        {
            if (t.substr(i, s.size()) == s)
                ans.push_back(i);

            //    cout << "HpppOO" << endl;
             //   if (match(&t[i],s))
              //  {
             //       cout << "Hey" << endl;
              //      ans.push_back(i);
              //  }


        }
    }

    return ans;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
