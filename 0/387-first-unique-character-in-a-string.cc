class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> pos(26, -1);
        for (int i=0; i<s.length(); i++) {
            int index = s[i]-'a';
            if (pos[index] >= 0) pos[index] = s.length() + 1;
            else pos[index] = i;
        }
        int minPos = s.length() + 1;
        for (int i=0; i<26; i++) {
            if (pos[i] == -1) continue;
            minPos = min(minPos, pos[i]);
        }
        if (minPos == s.length() + 1) return -1;
        return minPos;
    }
};
