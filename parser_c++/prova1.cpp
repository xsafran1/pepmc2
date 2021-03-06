#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;


vector <double> segmentErr (vector <double> x, vector <double> y)
{


       // Find out size of x
       int nx = x.size();
       int ny = y.size();

       vector <double>  result (3, 0.0);

       if (nx != ny)
       {
           cout << "Error in segmentErr: nx is not consistent with ny\n";
           return result;
       }

       // Compute line segment coefficients

       double a = (y[nx-1] - y[0]) / (x[nx-1] - x[0]);
       double b = (y[0] * x[nx-1] - y[nx-1] * x[0]) / (x[nx-1] - x[0]);

       // Compute error for above line segment

       double e = 0;

       /*for (int k=0; k < nx; k++)
       {
            e += pow((y[k] - a * x[k] - b),2)/(pow(a,2) + 1);
       }*/

	   for (int k=0; k < nx; k++)
	   {
		    e += pow((y[k] - a * x[k] - b),2);
	   }
	   e /= (pow(a,2) + 1);

       result[0] = e;
       result[1] = a;
       result[2] = b;

       return result;
}


vector <double> optimalGlobalLinearApproximation (vector <double> x, vector < vector <double> > y, int n_segments)
{

       int n_points = x.size();
       int n_curves = y.size();

       vector <vector <double> > mCost (n_points, vector <double>(n_segments, INFINITY));
       vector <vector <double> > hCst  (n_points, vector <double>(n_points,   INFINITY));

       mCost[1][0] = 0.0;

       vector <vector <int> > father (n_points, vector <int> (n_segments, 0));



       for (int n=1; n < n_points; n++)
       {
            double temp = -1 * INFINITY;

            //cout << "temp =" << temp << "\n";

            for (int ic=0; ic < n_curves; ic++)
            {
                 vector <double> v1 (x.begin(),          x.begin() + n+1);
                 vector <double> v2 (y[ic].begin(),      y[ic].begin() + n+1);
                 vector <double> seg_err = segmentErr(v1, v2);

                 temp = max(seg_err[0], temp);
            }

            mCost [n][0]  = temp;
            father[n][0]  = 0;
            //cout << " n=" << n << " mCost[" << n << "][0]=" << temp << " father[" << n << "][0]=" << father[n][0] << "\n";
       }



       double minErr, currErr;
       int    minIndex;

       for (int m=1; m < n_segments; m++)
       {
            cout << "segment m=" << m << "\n";
            for (int n=2; n < n_points; n++)
            {

                minErr   = mCost[n-1][m-1];
                minIndex = n - 1;

                for (int i=m; i <= n-2; i++)
                {
                    if (hCst[i][n]==INFINITY)
                    {
                        double temp = -1 * INFINITY;

                        for (int ic=0; ic < n_curves; ic++)
                        {
                             vector <double> v1 (x.begin() + i,          x.begin() + n+1);
                             vector <double> v2 (y[ic].begin() + i, y[ic].begin() + n+1);
                             vector <double> seg_err = segmentErr(v1, v2);

                             temp = max(seg_err[0], temp);
                        }

                        hCst[i][n] = temp;
                    }

                    currErr = mCost[i][m-1] + hCst[i][n];

                    if (currErr < minErr)
                    {
                        minErr   = currErr;
                        minIndex = i;
                    }
                }
               mCost[n][m]  = minErr;
               father[n][m] = minIndex;
         //  cout << " n=" << n << " mCost[" << n << "][" << m << "]=" << mCost[n][m] << " father[" << n << "][" << m << "]=" << father[n][m] << "\n";
        }
    }

    vector <int>     ib (n_segments+1, 0  );
    vector <double>  xb (n_segments+1, 0.0);



    ib[n_segments] = n_points-1;
    xb[n_segments] = x[ib[n_segments]];
    //cout << "x[ib[n_segments]]=" << x[ib[n_segments]] << "\n";
    for (int i=n_segments-1; i >= 0; i--)
    {
         ib[i] = father[ib[i+1]][i];
         xb[i] = x[ib[i]];
         //cout << "x" << n_points - i << "=" << xb[i] << "\n";
    }


    for (int i=0; i < n_segments + 1; i++)
    {
        cout << "x[" << i << "] =" << xb[i] << "\n";

    }

    return xb;

}




vector <double> optimalFastGlobalLinearApproximation2 (vector <double> x, vector < vector <double> > y, int n_segments)
{

	int n_points = x.size();
	int n_curves = y.size();

	vector <vector <double> > mCost (n_points, vector <double>(n_segments, INFINITY));
	vector <vector <double> > hCst  (n_points, vector <double>(n_points,   INFINITY));

	mCost[1][0] = 0.0;

	vector <vector <int> > father (n_points, vector <int> (n_segments, 0));





	for (int n=1; n < n_points; n++)
	{
		double temp = -1 * INFINITY;

		//cout << "temp =" << temp << "\n";

		for (int ic=0; ic < n_curves; ic++)
		{
			vector <double> v1 (x.begin(),          x.begin() + n+1);
			vector <double> v2 (y[ic].begin(),      y[ic].begin() + n+1);
			vector <double> seg_err = segmentErr(v1, v2);

			temp = max(seg_err[0], temp);
		}

		mCost [n][0]  = temp;
		father[n][0]  = 0;
		//cout << " n=" << n << " mCost[" << n << "][0]=" << temp << " father[" << n << "][0]=" << father[n][0] << "\n";
	}


	vector < vector <double> > sy2 (n_curves, vector <double> (n_points, 0.0));
	vector < vector <double> > sy  (n_curves, vector <double> (n_points, 0.0));
	vector < vector <double> > sxy (n_curves, vector <double> (n_points, 0.0));

	vector <double>  sx2 (n_points, 0);
	vector <double>  sx  (n_points, 0);

	for (int ic=0; ic < n_curves; ic++)
	{
		sy2[ic][0] = y[ic][0] * y[ic][0];
		sy [ic][0] = y[ic][0];
		sxy[ic][0] = y[ic][0] * x[0];
		for (int ip=1; ip < n_points; ip++)
		{
			sy2[ic][ip] = sy2[ic][ip-1] + (y[ic][ip] * y[ic][ip]);
			sy [ic][ip] = sy [ic][ip-1] + (y[ic][ip]);
			sxy[ic][ip] = sxy[ic][ip-1] + (y[ic][ip] * x[ip]);
		}
	}



	sx2[0] =          x[0] * x[0];
	sx [0] =          x[0];
	for (int ip=1; ip < n_points; ip++)
	{
	    sx2[ip] = sx2[ip-1] + (x[ip] * x[ip]);
	    sx [ip] = sx [ip-1]  + x[ip];
	}

	cout << "ciao mondo !!!\n";




	double minErr, currErr;
	int    minIndex;

	for (int m=1; m < n_segments; m++)
	{
		cout << "segment m=" << m << "\n";
		for (int n=2; n < n_points; n++)
		{

			minErr   = mCost[n-1][m-1];
			minIndex = n - 1;

			for (int i=m; i <= n-2; i++)
			{
				if (hCst[i][n]==INFINITY)
				{
					double temp = -1 * INFINITY;

					for (int ic=0; ic < n_curves; ic++)
					{

						double a       = (y[ic][n] - y[ic][0]) / (x[n] - x[0]);
						double b       = (y[ic][0] * x[n] - y[ic][n] * x[0]) / (x[n] - x[0]);
						double seg_err = (sy2[ic][n] - sy2[ic][i-1]) - 2 * a * (sxy[ic][n] - sxy[ic][i-1]) - 2 * b * (sy[ic][n] - sy[ic][i-1]) + a * a * (sx2[n] - sx2[i-1]) + 2 * a * b * (sx[n] - sx[i-1]) + b * (n - i);

						//vector <double> v1 (x.begin() + i,          x.begin() + n+1);
						//vector <double> v2 (y[ic].begin() + i, y[ic].begin() + n+1);
						//vector <double> seg_err = segmentErr(v1, v2);

						temp = max(seg_err, temp);
					}

					hCst[i][n] = temp;
				}

				currErr = mCost[i][m-1] + hCst[i][n];

				if (currErr < minErr)
				{
					minErr   = currErr;
					minIndex = i;
				}
			}
			mCost[n][m]  = minErr;
			father[n][m] = minIndex;
			//  cout << " n=" << n << " mCost[" << n << "][" << m << "]=" << mCost[n][m] << " father[" << n << "][" << m << "]=" << father[n][m] << "\n";
        }
    }

    vector <int>     ib (n_segments+1, 0  );
    vector <double>  xb (n_segments+1, 0.0);



    ib[n_segments] = n_points-1;
    xb[n_segments] = x[ib[n_segments]];
    cout << "x[ib[n_segments]]=" << x[ib[n_segments]] << "\n";
    for (int i=n_segments-1; i >= 0; i--)
    {
		ib[i] = father[ib[i+1]][i];
		xb[i] = x[ib[i]];
		// cout << "x" << n_points - i << "=" << xb[i] << "\n";
    }


    for (int i=0; i < n_segments + 1; i++)
    {
        cout << "x[" << i << "] =" << xb[i] << "\n";

    }

    return xb;

}




vector <double>  generateXPoints (double ai, double bi, int num_segments)
{
	   double a = ai;
	   double b = bi;

	   vector <double > x;

	   double dx= (b-a)/(num_segments-1);

	   for (int i=0; i < num_segments; i++)
	   {
		   double cx = a + dx*i;
		   x.push_back(cx);
	   }

	   return x;
}


vector < vector <double> > generateYPoints1 (vector <double> x)
{
	   vector <vector <double> > curves;

	   vector <double > y1, y2, y3;

	   double cx, cy1, cy2, cy3;

	   for (int i=0; i < x.size(); i++)
       {
			cx = x[i];
			cy1 = ((1 + tanh(2.0994 * (cx - 0.9087)))/2.0);
			cy2 = (cx - 0.3)*(1.55 - cx)/0.11;
			cy3 = 1/(30.0181 + (-14.5112) * (1 + tanh(2.0458 * (cx - 0.65))));
            std::cout << "i=" << i << " x=" << cx << " cy1="  <<  cy1 << " cy2=" << cy2 << " cy3=" << cy3 << "\n";
            y1.push_back(cy1);
            y2.push_back(cy2);
            y3.push_back(cy3);
        }

        curves.push_back(y1);
        curves.push_back(y2);
        curves.push_back(y3);

		return curves;
}



vector < vector <double> > generateYPoints2 (vector <double> x)
{
	vector <vector <double> > curves;

	vector <double > y1, y2;

	double cx, cy1, cy2;

	for (int i=0; i < x.size(); i++)
	{
		cx = x[i];
		cy1 = cx/(0.5 + cx);
		cy2 = (cx*cx)/(16 + cx*cx);
		y1.push_back(cy1);
		y2.push_back(cy2);
	}

	curves.push_back(y1);
	curves.push_back(y2);

	return curves;
}

class Sigmoid {
public:
    bool positive;
    std::string var;
    double k;
    double theta;
    double a;
    double b;
    double accuracy = 1.0;
    bool isInverse = false;

public:
    Sigmoid() {}
    Sigmoid(bool pos,std::string v, double k, double t, double a, double b) : positive(pos), var(v), k(k), theta(t), a(a), b(b) {}
    Sigmoid(bool pos,std::string v, double k, double t, double a, double b, double acc) : positive(pos), var(v), k(k), theta(t), a(a), b(b), accuracy(acc) {}
    Sigmoid(bool pos,std::string v, double k, double t, double a, double b, bool inv) : positive(pos), var(v), k(k), theta(t), a(a), b(b), isInverse(inv) {}
    Sigmoid(bool pos,std::string v, double k, double t, double a, double b, double acc, bool inv) : positive(pos), var(v), k(k), theta(t), a(a), b(b), accuracy(acc), isInverse(inv) {}

    std::vector<double> enumerateYPoints(std::vector<double> x) {

        std::vector<double> y;
        double tempA = a;
        double tempB = b;

        if(isInverse) {
            if(!positive) {
                tempA = b;
                tempB = a;
            }

            for(int i = 0; i < x.size(); i++) {
                //y.push_back((1/tempA) + ((1/tempB) - (1/tempA))*((1 + tanh(k*(x.at(i) - (theta + log(tempB/tempA)/(2*k)))))*0.5));
                y.push_back(1/(tempA + (tempB - tempA)*((1 + tanh(k*(x.at(i) - theta)))*0.5)));
            }

        } else {
            if(!positive) {
                tempA = b;
                tempB = a;
            }

            for(int i = 0; i < x.size(); i++) {
                y.push_back(tempA + (tempB - tempA)*((1 + tanh(k*(x.at(i) - theta)))*0.5));
            }
        }
        return y;
    }
};


// TAKZE FUNKCIA KTORA BUDE NEJAKYM SPOSOBOM BRAT SIGMOIDY (BUD VSETKY A Z NICH SI VYBERE ALEBO UZ DOSTANE TI SPRAVNE)
// NAJDE NAJKRAJNEJSIE THRESHOLDY A POMOCOU FUNKCIE generateXPoints() VYGENERUJE X-OVE SURADNICE A POMOCOU NICH
// VYPOCITA A ULOZI VSETKY Y-OVE HODNOTY DO vector<vector<double> > KTORY NAKONEC AJ ODOVZDA CEZ RETURN
// TREBA MYSLET AJ NA TO ZE vector<double> x BUDE TREBA TIEZ NEJAKO ODOVZDAT VON !!!
vector<vector<double> > generateSpace(vector<Sigmoid> s, vector<double> &x, int numOfX) {

    vector<vector<double> > y;

    if(s.size() > 0) {

        double intervalDeviationParam = 1.5;

        double min = s.at(0).theta - (2.0 / s.at(0).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou
        double max = s.at(0).theta + (2.0 / s.at(0).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou

        if(s.size() > 1) {

            for(int i = 1; i < s.size(); i++) {

                double tempMin = s.at(i).theta - (2.0 / s.at(i).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou
                double tempMax = s.at(i).theta + (2.0 / s.at(i).k) * intervalDeviationParam;       //TODO: bude treba .theta a .k nahradit spravnou funkciou

                if(tempMin < min) {
                    min = tempMin;
                }
                if(tempMax > max) {
                    max = tempMax;
                }
            }
        }

        if(numOfX != 0) {
            x = generateXPoints(min, max, numOfX);
        } else {
            x = generateXPoints(min, max, (max - min)*100);
        }

        for(int i = 0; i < s.size(); i++) {
            y.push_back(s.at(i).enumerateYPoints(x));
        }
    }

    return y;
}



vector<double> computeThresholds(vector<Sigmoid> s, int numOfSegments, int numOfX = 0) {

    int defaultNumOfSegments = 1;

    if(numOfSegments > defaultNumOfSegments)
        defaultNumOfSegments = numOfSegments;

    cout << "NUMBER OF SEGMENTS = " << defaultNumOfSegments << endl;

    //TODO: treba sa dohodnut ohladom obsahu hranatych zatvoriek u jednotlivych sigmoidov


    vector<double> xPoints;
    vector<vector<double> > curves = generateSpace(s,xPoints,numOfX);
    vector<double> segmentsPoints;

    clock_t start, finish;          //TODO: neskor zmazat
    double durationInSec;           //TODO: neskor zmazat
/*
    start = clock();                //TODO: neskor zmazat
    segmentsPoints = optimalFastGlobalLinearApproximation2 (xPoints, curves, defaultNumOfSegments);

    finish = clock();               //TODO: neskor zmazat
    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;          //TODO: neskor zmazat
    cout << "duration = " << durationInSec << " sec. Found = ";          //TODO: neskor zmazat
    for(int i = 0; i < segmentsPoints.size(); i++)
        cout << segmentsPoints.at(i) << ",";
    cout << endl;
*/

    start = clock();                //TODO: neskor zmazat
    segmentsPoints = optimalGlobalLinearApproximation (xPoints, curves, defaultNumOfSegments);

    finish = clock();               //TODO: neskor zmazat
    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;      //TODO: neskor zmazat
    cout << "duration = " << durationInSec << " sec. Found = ";     //TODO: neskor zmazat
    for(int i = 0; i < segmentsPoints.size(); i++)                  //TODO: neskor zmazat
        cout << segmentsPoints.at(i) << ",";                        //TODO: neskor zmazat
    cout << endl;                                                   //TODO: neskor zmazat

    return segmentsPoints;
}



vector<Sigmoid> generateTestingCurves(int whichCase) {
    vector<Sigmoid> curves;
    switch(whichCase) {
        case 0:
            curves.push_back(Sigmoid(true,"x",2.0,0.0,0.0,1.0));
            break;
        case 1:
            curves.push_back(Sigmoid(true,"x",2.0,0.0,0.0,1.0));
            curves.push_back(Sigmoid(true,"x",2.0,3.0,0.0,5.0));
            curves.push_back(Sigmoid(true,"x",1.5,0.0,0.0,1.0));
            curves.push_back(Sigmoid(true,"x",2.5,1.0,2.0,4.0));
            break;
        case 2:
            curves.push_back(Sigmoid(true,"x",2.0,0.0,0.0,1.0));
            curves.push_back(Sigmoid(false,"x",2.0,3.0,0.0,5.0));
            curves.push_back(Sigmoid(false,"x",2.0,0.0,1.0,2.0,true));
            curves.push_back(Sigmoid(true,"x",2.5,1.0,2.0,4.0));
            break;
        case 3:
            //curves.push_back(Sigmoid(true,"x",1.0,2.0 + log(3.0/4.0)/2,1/4.0,1/3.0));         //skupina 4
            //curves.push_back(Sigmoid(false,"x",1.0,2.0 + log(3.0/4.0)/2,1/3.0,1/4.0));        //skupina 4
            //curves.push_back(Sigmoid(false,"x",1.0,2.0,3.0,4.0,true));                       //skupina 1
            //curves.push_back(Sigmoid(true,"x",1.0,2.0 + log(4.0/3.0)/2,1/4.0,1/3.0));       //skupina 1
            //curves.push_back(Sigmoid(false,"x",1.0,2.0 + log(4.0/3.0)/2,1/3.0,1/4.0));      //skupina 1
            curves.push_back(Sigmoid(true,"x",1.0,2.0,3.0,4.0,true));                       //skupina 3
            curves.push_back(Sigmoid(false,"x",1.0,2.0 + log(3.0/4.0)/2,1/4.0,1/3.0));      //skupina 3
            curves.push_back(Sigmoid(true,"x",1.0,2.0 + log(3.0/4.0)/2,1/3.0,1/4.0));       //skupina 3
            //curves.push_back(Sigmoid(true,"x",1.0,2.0 + log(4.0/3.0)/2,1/3.0,1/4.0));         //skupina 2
            //curves.push_back(Sigmoid(false,"x",1.0,2.0 + log(4.0/3.0)/2,1/4.0,1/3.0));        //skupina 2
            //curves.push_back(Sigmoid(false,"x",1.0,2.0,3.0,4.0));
            //curves.push_back(Sigmoid(true,"x",1.0,2.0,4.0,3.0));
            break;
    }
    return curves;
}

void computeRampFunctions() {
    // dostane alebo si zoberie priamo ako class method vector so vsetkymi sigmoidami a rozdeli ich podla Vars do skupin
    // postupne vsetky skupiny sigmoidov posle funkcii comuteThresholds, ktore zaroven ulozi medzi ostatne thresholdy
    // nasledne podla tychto novych thresholdov vytvori rampy pre vsetky sigmoidy zo skupiny a ulozi medzi rampy
    // nakoniec mozno zmaze sigmoidy ak uz nebudu treba
}

int main() {

    int testingCase = 3;
    vector<double> segmentsPoints;
    vector<Sigmoid> curves = generateTestingCurves(testingCase);

    segmentsPoints = computeThresholds(curves,1,0);
    segmentsPoints = computeThresholds(curves,12,0);

    for(int j = 0; j < curves.size(); j++) {
        stringstream ss;
        ss << j;
        string fileName = "test_curve" + ss.str() + ".dat";
        ofstream out(fileName,ofstream::out | ofstream::trunc);
        if(out.is_open()) {
            for(int i = 0; i < segmentsPoints.size(); i++) {
                out << segmentsPoints.at(i) << "\t" << curves.at(j).enumerateYPoints(segmentsPoints).at(i) << "\n";
            }
            out.close();
        }
    }

/*
    vector <vector <double > >::iterator i_curve;
    vector <double>::iterator i_point;

    vector <double > x = generateXPoints (0.3, 1.55, 500);


    vector < vector <double> > curves = generateYPoints1 (x);


    int n_segments = 25;                          //number of segments

    int n_points = x.size();                      //number of points
    std::cout << " n_points= " << n_points << "\n";

    int n_curves = curves.size();                 //number of curves
    std::cout << " n_curves= " << n_curves << "\n";

    clock_t start, finish;


    start = clock();

    vector <double> final_x = optimalFastGlobalLinearApproximation2 (x, curves, n_segments);


    finish = clock();

    double durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;


    cout << "duration= " << durationInSec << " sec. \n";


	start = clock();

    final_x = optimalGlobalLinearApproximation (x, curves, n_segments);


    finish = clock();

    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;


    cout << "duration= " << durationInSec << " sec. \n";



	x = generateXPoints (0, 6.0, 500);

	curves = generateYPoints2 (x);


	start = clock();

    final_x = optimalGlobalLinearApproximation (x, curves, n_segments);


    finish = clock();

    durationInSec = (double)(finish - start) / CLOCKS_PER_SEC;


    cout << "duration= " << durationInSec << " sec. \n";
*/
}

