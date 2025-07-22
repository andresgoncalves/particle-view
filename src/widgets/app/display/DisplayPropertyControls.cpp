#include "DisplayPropertyControls.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/dialogs/ColorDialog.h>

DisplayPropertyControls::DisplayPropertyControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Propiedades", parent}
{
  // Create particle color control
  auto particleColorControl = new ColorControl{"Partícula", true, this};
  // Connect checkbox callback
  connect(particleColorControl->getCheckBox(), &QCheckBox::checkStateChanged, this, [&appContext](Qt::CheckState checkState)
          { appContext.displayController.setDisplayParticles(checkState != Qt::Unchecked); });
  // Connect color change callback
  connect(particleColorControl->getColorButton(), &ColorButton::clicked, this,
          [=, this, &appContext]()
          {
            auto colorDialog = new ColorDialog{appContext, this};
            colorDialog->setColorStrategy(appContext.displayController.getDisplayParticles().second.get());

            if (colorDialog->exec() == QDialog::Accepted)
              appContext.displayController.setDisplayParticles(colorDialog->getColorStrategy());

            colorDialog->deleteLater();
          });

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(particleColorControl);
  layout->setSpacing(0);
  layout->setContentsMargins({});

  // Add story property listener
  auto storyCallback = [=, this, &appContext]()
  {
    // Delete previous controls
    for (auto [property, control] : vectorColorControls)
    {
      layout->removeWidget(control);
      control->deleteLater();
    }
    vectorColorControls.clear();

    // Create vector controls
    auto story = appContext.animationController.getStory();
    for (auto property : story.vectorProperties)
    {
      // Create vector color control
      auto vectorColorControl = new ColorControl{property.c_str(), true, this};
      vectorColorControl->getCheckBox()->setChecked(appContext.displayController.getDisplayVector(property).first);
      vectorColorControl->getColorButton()->setColorStrategy(appContext.displayController.getDisplayVector(property).second.get());
      // Connect checkbox callback
      connect(vectorColorControl->getCheckBox(), &QCheckBox::checkStateChanged, this, [=, &appContext](Qt::CheckState checkState)
              { appContext.displayController.setDisplayVector(property, checkState != Qt::Unchecked); });
      // Connect color change callback
      connect(vectorColorControl->getColorButton(), &ColorButton::clicked, this,
              [=, this, &appContext]()
              {
                auto colorDialog = new ColorDialog{appContext, this};
                colorDialog->setColorStrategy(appContext.displayController.getDisplayVector(property).second.get());

                if (colorDialog->exec() == QDialog::Accepted)
                  appContext.displayController.setDisplayVector(property, colorDialog->getColorStrategy());

                colorDialog->deleteLater();
              });

      // Save checkbox
      layout->addWidget(vectorColorControl);
      vectorColorControls[property] = vectorColorControl;
    }
  };
  storyCallback();
  appContext.animationController.storyObservable.subscribe(this, storyCallback);

  // Add display particles listener
  auto displayParticlesCallback = [=](DisplayController::DisplayProperty displayParticles)
  {
    particleColorControl->getCheckBox()->setChecked(displayParticles.first);
    particleColorControl->getColorButton()->setColorStrategy(displayParticles.second.get());
  };
  appContext.displayController.displayParticlesObservable.subscribe(this, displayParticlesCallback, true);

  // Add displayed vectors listener
  auto displayVectorsCallback = [=, this](std::map<std::string, DisplayController::DisplayProperty> displayVectors)
  {
    for (auto [property, control] : vectorColorControls)
    {
      auto it = displayVectors.find(property);
      if (it != displayVectors.end())
      {
        control->getCheckBox()->setChecked(it->second.first);
        control->getColorButton()->setColorStrategy(it->second.second.get());
      }
      else
      {
        control->getCheckBox()->setChecked(false);
      }
    }
  };
  appContext.displayController.displayVectorsObservable.subscribe(this, displayVectorsCallback);
}

DisplayPropertyControls::~DisplayPropertyControls()
{
  appContext.animationController.storyObservable.unsubscribe(this);
  appContext.displayController.displayParticlesObservable.unsubscribe(this);
  appContext.displayController.displayVectorsObservable.unsubscribe(this);
}
