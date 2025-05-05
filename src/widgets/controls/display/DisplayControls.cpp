#include "DisplayControls.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QCheckBox>

DisplayControls::DisplayControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, ControlSection{"Visualización", parent}
{
  auto layout = new QVBoxLayout{content};
  layout->setContentsMargins(0, 0, 0, 0);

  particleCheckBox = new QCheckBox{"Partícula", this};
  particleCheckBox->setChecked(appContext.displayController.getDisplayParticles());
  connect(particleCheckBox, &QCheckBox::checkStateChanged, this, [=, &appContext](Qt::CheckState checkState)
          { appContext.displayController.setDisplayParticles(checkState != Qt::Unchecked); });

  layout->addWidget(particleCheckBox);

  refreshProperties();

  auto displayedVectorsCallback = [&](std::set<std::string> displayedVectors)
  {
    for (auto [property, checkBox] : vectorCheckBoxes)
      checkBox->setChecked(displayedVectors.contains(property));
  };

  appContext.displayController.displayedVectorsObservable.subscribe(this, displayedVectorsCallback);
  appContext.animationController.storyObservable.subscribe(this, [&]
                                                           { refreshProperties(); });
}

DisplayControls::~DisplayControls()
{
  appContext.displayController.displayedVectorsObservable.unsubscribe(this);
}

void DisplayControls::refreshProperties()
{
  for (auto [property, checkBox] : vectorCheckBoxes)
  {
    content->layout()->removeWidget(checkBox);
    checkBox->deleteLater();
  }
  vectorCheckBoxes.clear();

  auto story = appContext.animationController.getStory();
  for (auto property : story.vectorProperties)
  {
    auto checkBox = new QCheckBox{property.c_str(), this};
    checkBox->setChecked(appContext.displayController.getDisplayVector(property));
    connect(checkBox, &QCheckBox::checkStateChanged, this, [=, this](Qt::CheckState checkState)
            { appContext.displayController.setDisplayVector(property, checkState != Qt::Unchecked); });

    content->layout()->addWidget(checkBox);

    vectorCheckBoxes[property] = checkBox;
  }
}
