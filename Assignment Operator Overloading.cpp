//http://www.lintcode.com/en/problem/assignment-operator-overloading-c-only/

class Solution {
public:
    char *m_pData;
    int len;

    Solution() {
        this->m_pData = NULL;
        len = -1;
    }
    Solution(char *pData) {
        len = strlen(pData);
        this->m_pData = new char[len];
        strcpy(m_pData, pData);
    }


    Solution & operator=(const Solution &object) {

        if (m_pData == object.m_pData)
            return *this;
        if (m_pData)
            delete [] m_pData;

        len = object.len;

        if (object.m_pData){
            m_pData = new char[len+1];//NULL included
            strcpy(m_pData, object.m_pData);
        }else{
            m_pData = NULL;
        }

        return *this;
    }
};
