#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <set>
#include <string>

#include "Observable.h"

class DisplayController
{
public:
  DisplayController();

  void toggleParticles();
  void setDisplayParticles(bool value);

  void toggleVector(std::string property);
  void setDisplayVector(std::string property, bool value);

  bool getDisplayParticles() const;
  bool getDisplayVector(std::string property) const;
  std::set<std::string> getDisplayedVectors() const;

  Observable<bool> displayParticlesObservable = displayParticles;
  Observable<std::set<std::string>> displayedVectorsObservable = displayedVectors;

private:
  bool displayParticles = true;
  std::set<std::string> displayedVectors;
};

#endif