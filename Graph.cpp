#include "Graph.h"

using namespace std;




int isdigit(const string& tmp) {
    for (char i : tmp) {
        if (!isdigit(i))
            return 0;
    }
    return 1;
}


ostream& operator<< (ostream& os, const list<int>& V) {
    for(auto it : V)
        os << it << " ";
    return os << "\n";
}





Edge::Edge(int a, int b, int c) : v1(a), v2(b), length(c) {}


void Edge::Change(int a, int b, int c) {
    v1=a; v2=b; length=c;
}



int Edge::Get(int n) const {
    switch(n) {
        case 1:
            return v1;
        case 2:
            return v2;
        default:
            return length;
    }
}



bool operator<(Edge& e1, Edge& e2) {
    return (e1.length < e2.length);
}

bool operator==(Edge& e1, Edge& e2) {
    return (e1.length==e2.length);
}



bool vert_inq(Edge &e1, Edge &e2) {
    return (e1.v1 < e2.v1);
}


ostream& operator<< (ostream& os, const Edge& e) {
    return os << "{ " << e.v1 << " ; " << e.v2 << " }";
}


ostream& operator<< (ostream& os, const list<Edge>& E) {
    for(auto it : E)
        os << it << endl;
    return os << "\n";
}



Graph::Graph() {

    string str; char k[2]; int l=0;

    int v[2]={0,0}, j=0,i=0;
    Edge e(v[0],v[1],0);
    cout << "Enter Edges:" << endl;
    getline(cin,str);

    cout << "Does Edges have weight? [ Y / N ]\t"; cin >> k[0];
    cout << "Does Graph Orientated? [ Y / N ]\t"; cin >> k[1];
    char *tmp = strdup(str.c_str());
    char *token;
    token = strtok (tmp," ");


    while(token != nullptr) {
        if (isdigit(tmp)==1) {


            v[i]=stoi(token);
            i++;
            j++;
            if (i==2) {

                if ((k[0]=='Y') || (k[0]=='y')) {
                    cout << "Enter weight of the Edge  " << v[0] << " - " << v[1] << "  =  ";
                    cin >> l;
                    e.Change(v[0], v[1], l);
                    El.push_back(e);
                    if ((k[1]!='Y') || (k[1]!='y')) {
                        e.Change(v[1],v[0],l);
                        El.push_back(e);
                    }
                }
                else {
                    e.Change(v[0], v[1], 1);
                    El.push_back(e);
                    if ((k[1]!='Y') || (k[1]!='y')) {
                        e.Change(v[1],v[0],1);
                        El.push_back(e);
                        }
                }
                Vert.push_back(v[0]), Vert.push_back(v[1]);
                i=0;
            }
            token = strtok(nullptr, " ");
        }
    }
    if (j % 2 !=0)
        Vert.push_back(v[0]);


    El.sort(vert_inq);
    Vert.sort();
    Vert.unique();

}


list<int>& Graph::Get_V() {
    return Vert;

}

list<Edge>& Graph::Get_E() {
            return El;
    }





void Graph::Del_El(list<Edge> &l, list<Edge>::iterator &it) {

for(list<Edge>::iterator it2=l.begin(); it2!=l.end(); it2++) {
    if ((it2->Get(1) == it->Get(2)) && (it2->Get(2) == it->Get(1))) {
        l.erase(it2);
        break;
    }
}
}





list<int>::iterator Graph::Rand_V() {
    srand(time(NULL));
    int r = rand() % Vert.size() + 1;
    list<int>::iterator it=Vert.begin();
    advance(it, r-1);
    //cout << *it << endl;
    return it;
}


int Graph::Vert_Degree(int vert) {
    int k=0;
    for (auto &it : El)
        if (vert==it.Get(1))
            k++;
        return k;

}

void Graph::FloydAlg(int **distance) {
    int n=(int)Vert.size();
    for (auto it : El)
        distance[V1-1][V2-1]=LEN;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++) {
                if (j==k)
                    distance[j][k]=0;
                else {
                        distance[j][k] = min(distance[j][k], distance[i][j] + distance[i][k]);
                }
        }


}


int *Graph::Radius() {
    int n=(int)Vert.size();
    int **distance;
    distance = new int *[n];
    for(int i=0; i<n; i++)
        distance[i]= new int [n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            distance[i][j]=MAX;
    FloydAlg(distance);
    int e[n];
    for(int i=0; i<n; i++) {
        e[i]=*std::max_element(distance[i],distance[i]+5);
    }
    for(int i=0; i<n; i++)
            delete []distance[i];
    delete[] distance;
    return std::max_element(e,e+n);

}


int *Graph::Diameter() {
    int n = (int) Vert.size();
    int **distance = new int *[n];
    for (int i = 0; i < n; i++)
        distance[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            distance[i][j] = MAX;
    FloydAlg(distance);
    int e[n];
    for (int i = 0; i < n; i++) {
        e[i] = *std::max_element(distance[i], distance[i] + 5);
    }
    for (int i = 0; i < n; i++)
        delete[]distance[i];
    delete[] distance;
    return std::min_element(e, e + n);
}


bool Graph::Is_Bridge(list<Edge> &l, int v1) {
    short k = 0;
        for(auto &ite : l)
            if( v1 == ite.Get(1 ) )
                k++;
    if(k > 1)
        return false;

    return true;
}



bool Graph::FleuryAlg(list<Edge> &l, list<int> &vert, int k, int a) {
    int v=a;
        for(list<Edge>::iterator it=l.begin(); it!=l.end(); it++) {
            if (v == it->Get(1) ) {
                if ( (l.size() <= 2 || !Is_Bridge(l, it->Get(2))) && !l.empty()) {

                    cout << v << " ";
                    v = it->Get(2);
                    if(l.size() <= 1)
                        l.erase(it);
                    else {
                        Del_El(l, it);
                        l.erase(it);
                    }
                    k++;
                    return FleuryAlg(l, vert, k, v);
                }
            }
            else if(l.empty())
                break;
        }
        if(k==vert.size())
            return true;

    return false;
}


string Graph::Is_Eulerian(int i) {
    int k=0; list<Edge> f = El;
    for(auto &it : Vert)
        if(Vert_Degree(it) % 2 == 0)
            k++;
    if (k!=Vert.size()) { // if all  vertexes are not even, then return false;
        return "None Eulerian Graph";
    }
    int c=k;
    cout << "Fleury's Algorithm is:" << endl;
    k=0;
    FleuryAlg(f, Vert, k, i);
    cout << i << endl; // Last vertex printed, 'cause it's a cycle and my algorithm is not much efficient
    if ( ( (Vert.size()-c) % 2 == 0) && (c!=Vert.size()))// Count of Odd Degrees are Even
        return "Half Eulerian Graph"; //Half Eulerian Graph

    return "Eulerian Graph";

}



string Graph::Is_Hamiltonian(int a) {
    int p = (int)Vert.size();
    for(int i=0; i<=p; i++) {
        if (Vert_Degree(i) < p / 2)
            return "None Hamiltonian Graph";
    }
    return "Hamiltonian Graph";
}



void Graph::Depth_FS(list<int> &s,int v) {
    s.push_back(v);
    for(auto &ite : El) {
        if (v == ite.Get(1))
            if(!(FIND(s,ite.Get(2)))) {
                return Depth_FS(s, ite.Get(2));


            }
    }
}




void Graph::Rec_Call(bool k, int v, list<int>& st) {
    st.clear();
    if(!k) {
        Depth_FS(st, v);
        for (auto itv: Vert) {
            if (std::find(st.begin(), st.end(), itv) == st.end()) {
                Depth_FS(st, itv);
            }

        }
        cout << st << endl;
    }

}



void Graph::Keys() {
    string k; int r=0;
    list<int> st;
    int a = 0;
    char b;
    while (true) {
        cin.ignore();
        cout << "Choose option:\n" << "1 - Check on Eulerian\t2 - Check on Hamiltonian\t3 - Depth First Search\n"
                                      "4 -  Graph's Radius and Diameter\t5 - Print Vertexes\t6 - Print Edges\n0/E - Exit\n" << "Your Choice:\t";
        getline(cin, k); NL
        for (char c: k) {
            if (c != ' ')
                switch (c) {
                    case '1': {
                        cout << "Random Vertex for Euler? [ Y / N ]\t";
                        cin >> b; NL
                        if ((b == 'Y') || (b == 'y')) {
                            r=*Rand_V();
                            cout << "Vertex number is  " << r << endl;
                            cout << Is_Eulerian(r) << endl;

                        }
                        else {
                            cout << "Type Vertex:\t";
                            cin >> a;
                            cout << Is_Eulerian(a) << endl;
                        }
                        break;
                    }
                    case '2': {
                        cout << "Random Vertex for Hamilton? [ Y / N ]\t";
                        cin >> b; NL
                        if ((b == 'Y') || (b == 'y')) {
                            r=*Rand_V();
                            cout << "Vertex number is  " << r << endl;
                            cout << Is_Hamiltonian(r) << endl;

                        }
                        else {
                            cout << "Type Vertex:\t";
                            cin >> a;
                            cout << Is_Hamiltonian(a) << endl;
                        }
                        break;
                    }
                    case '3': {

                        cout << "Random Vertex for DFS? [ Y / N ]\t";
                        cin >> b; NL
                        if ((b == 'Y') || (b == 'y')) {
                            r=*Rand_V();
                            cout << "Vertex number is " << r << endl;
                            Rec_Call(false, r, st);
                        }
                        else {
                            cout << "Type Vertex:\t";
                            cin >> a; NL
                            Rec_Call(false,a,st);
                        }
                        break;
                        }
                    case '4': {
                        cout << "Graph's Radius:  " << *Radius() << "\n" << "Graph's Diameter:  "<< *Diameter() << endl;
                        break;
                        // There's a bug: after printing values, option choice will appear after pressing ENTER
                    }
                    case '5': {
                        cout << "\n" << "Vertexes:\t" << Vert;
                        break;
                    }
                    case '6': {
                        cout << "Edges:\n" << El;
                        break;
                    }
                    default:
                        break;
                }
            if (c=='E' || c=='e' || c=='0') exit(0);
        }
    }

}