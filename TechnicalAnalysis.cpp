#include "TechnicalAnalysis.h"


std::mutex mtx;

std::vector<double> TechnicalAnalysis::getRSI()
{
 std::lock_guard<std::mutex> guard(mtx);
 return RSI;
}

std::vector<double> TechnicalAnalysis::getStoch()
{
  std::lock_guard<std::mutex> guard(mtx);
  return stochRSI;
}

std::vector<double> TechnicalAnalysis::getFifSMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return fiftySMA;
}

std::vector<double> TechnicalAnalysis::getHundSMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return hundredSMA;
}

std::vector<double> TechnicalAnalysis::getHundFifSMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return hundFifSMA;
}

std::vector<double> TechnicalAnalysis::getTwoHundSMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return twoHundSMA;
}

std::vector<double> TechnicalAnalysis::getFifEMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return fiftyEMA;
}

std::vector<double> TechnicalAnalysis::getHundEMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return hundredEMA;
}

std::vector<double> TechnicalAnalysis::getHundFifEMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return hundFifEMA;
}

std::vector<double> TechnicalAnalysis::getTwoHundEMA()
{
  std::lock_guard<std::mutex> guard(mtx);
  return twoHundEMA;
}

void TechnicalAnalysis::setFifSMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  fiftySMA.push_back(temp);
}

void TechnicalAnalysis::setHundSMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  hundredSMA.push_back(temp);
}

void TechnicalAnalysis::setHundFifSMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  hundFifSMA.push_back(temp);
}

void TechnicalAnalysis::setTwoHundSMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  twoHundSMA.push_back(temp);
}

void TechnicalAnalysis::setFifEMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  fiftyEMA.push_back(temp);
}

void TechnicalAnalysis::setHundEMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  hundredEMA.push_back(temp);
}

void TechnicalAnalysis::setHundFifEMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  hundFifEMA.push_back(temp);
}

void TechnicalAnalysis::setTwoHundEMA(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  twoHundEMA.push_back(temp);
}

void TechnicalAnalysis::setRSI(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  RSI.push_back(temp);
}

void TechnicalAnalysis::setStoch(const double &temp)
{
  std::lock_guard<std::mutex> guard(mtx);
  stochRSI.push_back(temp);
}

void TechnicalAnalysis::clearTAobj()
{
        RSI.clear();
        stochRSI.clear();
        fiftySMA.clear();
        hundredSMA.clear();
        hundFifSMA.clear();
        twoHundSMA.clear();
        fiftyEMA.clear();
        hundredEMA.clear();
        hundFifEMA.clear();
        twoHundEMA.clear();
}

/*
void TechnicalAnalysis::calcSD()
{
    double sum = 0.0, mean, standardDeviation = 0.0;

    for(int i = 0; i < 10; ++i)
        sum += data[i];

    mean = sum/10;

    for(i = 0; i < 10; ++i)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / 10);
}

*/
/*-------------------- START EMAs --------------------*/

void TechnicalAnalysis::calcFiftyEMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());

  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 50, j = 0;
  auto closePrices= HistoricalData.getClose();
  std::vector<double> tempEMA;

  for(int i = 0; i < period; i++)
    sum += closePrices[i];

  SMA = sum/period;
  tempEMA.push_back(SMA);
  setFifEMA(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (closePrices.size() - period); i++){
    tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
    j++;
    setFifEMA(tempEMA[j]);
  }
}

void TechnicalAnalysis::calcHundredEMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());

  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 100, j = 0;
  auto closePrices= HistoricalData.getClose();
  std::vector<double> tempEMA;

  for(int i = 0; i < period; i++)
    sum += closePrices[i];

  SMA = sum/period;
  tempEMA.push_back(SMA);
  setHundEMA(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (closePrices.size() - period); i++){
    tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
    j++;
    setHundEMA(tempEMA[j]);
  }
}

void TechnicalAnalysis::calcHundFiftyEMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());

  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 150, j = 0;
  auto closePrices= HistoricalData.getClose();
  std::vector<double> tempEMA;

  for(int i = 0; i < period; i++)
    sum += closePrices[i];

  SMA = sum/period;
  tempEMA.push_back(SMA);
  setHundFifEMA(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (closePrices.size() - period); i++){
    tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
    j++;
    setHundFifEMA(tempEMA[j]);
  }
}

void TechnicalAnalysis::calcTwoHundEMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());

  double SMA = 0.0, sum = 0.0, multipler = 0.0;
  int period = 200, j = 0;
  auto closePrices = HistoricalData.getClose();
  std::vector<double> tempEMA;

  for(int i = 0; i < period; i++)
    sum += closePrices[i];

  SMA = sum/period;
  tempEMA.push_back(SMA);
  setTwoHundEMA(SMA);
  multipler = 2/(period + 1);

  for(int i = period; i <= (closePrices.size() - period); i++){
    tempEMA.push_back((closePrices[i]-tempEMA[j])*multipler+tempEMA[j]);
    j++;
    setTwoHundEMA(tempEMA[j]);
  }
}

/*-------------------- END EMAs   --------------------*/


/*-------------------- START SMAs --------------------*/
void TechnicalAnalysis::calcFiftySMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());
  double sum;
  int period = 50;

  auto closePrices = HistoricalData.getClose();
  std::vector<double> tempSMA;

  for(int i = 0; i <= (closePrices.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += closePrices[j];

    setFifSMA(sum/period);
  }
}


void TechnicalAnalysis::calcHundredSMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());
  double sum;
  int period = 100;

  auto closePrices= HistoricalData.getClose();
  std::vector<double> tempSMA;

  for(int i = 0; i <= (closePrices.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += closePrices[j];

    setHundSMA(sum/period);
  }
}

void TechnicalAnalysis::calcHundFiftySMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());
  double sum;
  int period = 150;

  auto closePrices = HistoricalData.getClose();
  std::vector<double> tempSMA;

  for(int i = 0; i <= (closePrices.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += closePrices[j];

    setHundFifSMA(sum/period);
  }
}

void TechnicalAnalysis::calcTwoHundSMA(const JSONdata &HistoricalData)
{
  assert(!HistoricalData.isEmpty());
  double sum;
  int period = 200;

  auto closePrices = HistoricalData.getClose();
  std::vector<double> tempSMA;

  for(int i = 0; i <= (closePrices.size() - period); i++){
    sum = 0.0;

    for (int j = i; j < i + period; j++)
      sum += closePrices[j];

    setTwoHundSMA(sum/period);
  }
}
/*-------------------- END SMAs   --------------------*/


/*-------------------- START RSI  --------------------*/
void TechnicalAnalysis::calcRSI(const JSONdata &HistoricalData)
{
        assert(!HistoricalData.isEmpty());

        auto pushCurrentPeriod = [] (const std::vector<long double> &currPeri, std::vector<long double> &change){
                                         for(int i = 1; i < currPeri.size(); i++)
                                                 change.push_back(currPeri[i] - currPeri[i-1]);
                                 };

        std::vector<long double> gain, loss, change, avgGain, avgLoss, RS;
        auto closePrices = HistoricalData.getClose();

        //We need these if/else statements so program works when there hasn't been 250 data points yet.
        if(closePrices.size() > 250) {
                std::vector <long double> currentPeriod(closePrices.end()-250,closePrices.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        else{
                std::vector <long double> currentPeriod(closePrices.begin(),closePrices.end());
                pushCurrentPeriod(currentPeriod, change);
        }

        double sumGain = 0, sumLoss = 0;

        for(int i = 0; i < change.size(); i++) {
                change[i] > 0 ? gain.push_back(change[i]) : gain.push_back(0);
                change[i] < 0 ? loss.push_back(abs(change[i])) : loss.push_back(0);
                sumGain += gain[i];
                sumLoss += loss[i];
        }

        avgGain.push_back(sumGain/14);
        avgLoss.push_back(sumLoss/14);

        for(int i = 14, j = 1; i < gain.size(); i++) {
                avgGain.push_back(((avgGain[j-1] * 13)+ gain[i])/14);
                avgLoss.push_back(((avgLoss[j-1] * 13)+ loss[i])/14);
                j++;
        }

        for(int i = 0; i < avgGain.size(); i++) {
                RS.push_back(avgGain[i]/avgLoss[i]);
                setRSI(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
                //RSI.push_back(avgLoss[i] == 0 ? 100 : 100 - (100/(1+RS[i])));
              //  std::cout<<"RSI: " << RSI[i] << std::endl;
        }
        calcStochRSI();

        for(int i : RSI){
          std::cout<<std::endl<<i;
        }
}

void TechnicalAnalysis::calcStochRSI()
{
        assert(!RSI.empty());

        auto copy = [] (const std::vector<double> &RSI, std::vector<double> &temp, const int &loc){
                            for(int i = 13; i >= 0; i--)
                                    temp.push_back(RSI[loc-i]);
                    };

        std::vector<double> tempVec;
        auto tempRSI = getRSI();


        for(int i = 13; i <tempRSI.size(); i++) {
                copy(tempRSI,tempVec,i);
                auto lowIt= *std::min_element(tempVec.begin(), tempVec.end());
                auto highIt= *std::max_element(tempVec.begin(), tempVec.end());
                setStoch((tempVec.back()-lowIt)/(highIt-lowIt));
                tempVec.clear();
        }
}
/*-------------------- END RSI  --------------------*/
