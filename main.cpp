#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string serialNum;
string versionNum;
vector<string> serialNums;
vector<string>::iterator it;
map<string,int> verMap;

int main() {
  
  fstream vpnLog;
  vpnLog.open("openvpn.log", ios::in);
  if (vpnLog.is_open()) {
    string logLine;
    while (getline(vpnLog, logLine)) {
      if (logLine.find("IV_VER") < logLine.size()){
        // cout << logLine << "\n";
        for(int i = 0; i < logLine.size(); i++) {
          if (isalpha(logLine[i]) && logLine[i+12] == '/') {
            serialNum = logLine.substr(i,12);
            
          } else if (logLine[i] == '=' && logLine[i+2] == '.') {
            versionNum = logLine.substr(i+1);
            it = find(serialNums.begin(), serialNums.end(), serialNum);
            if (it == serialNums.end()) {
              serialNums.push_back(serialNum);
              if (verMap[versionNum]) {
                verMap[versionNum] += 1;
              } else {
                verMap[versionNum] = 1;
              }
            }
          }
        }
      }
    }
    for(const auto& x: verMap){
      cout << x.first << ": " << x.second << '\n';
    }
    vpnLog.close();
  }

  return 0;
}