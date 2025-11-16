#include "DisplayPropertyControls.h"

#include <QtWidgets/QVBoxLayout>

#include <widgets/app/dialogs/ColorDialog.h>

DisplayPropertyControls::DisplayPropertyControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{"Propiedades", parent}
{
  // Create particle color control
  auto particleColorControl = new ColorControl{"Partícula", true, this};
  particleColorControl->getCheckBox()->setChecked(appContext.displayController.getParticleRule().isVisible());
  particleColorControl->getColorButton()->setColorStrategy(appContext.displayController.getParticleRule().getColorStrategy().get());
  // Connect checkbox callback
  connect(particleColorControl->getCheckBox(), &QCheckBox::checkStateChanged, this, [&appContext](Qt::CheckState checkState)
          { 
            auto updatedRule = appContext.displayController.getParticleRule();
            updatedRule.setVisible(checkState != Qt::Unchecked);
            appContext.displayController.setParticleRule(updatedRule); });
  // Connect color change callback
  connect(particleColorControl->getColorButton(), &ColorButton::clicked, this,
          [=, this, &appContext]()
          {
            auto colorDialog = new ColorDialog{appContext, this};
            colorDialog->setColorStrategy(appContext.displayController.getParticleRule().getColorStrategy().get());
            if (colorDialog->exec() == QDialog::Accepted)
            {
              auto updatedRule = appContext.displayController.getParticleRule();
              updatedRule.setColorStrategy(colorDialog->getColorStrategy());
              appContext.displayController.setParticleRule(updatedRule);
            }
            colorDialog->deleteLater();
          });

  // Build layout
  auto layout = new QVBoxLayout{content};
  layout->addWidget(particleColorControl);
  layout->setSpacing(0);
  layout->setContentsMargins({});

  // Add vector controls
  auto addVectorControls = [=, this, &appContext]()
  {
    for (auto [propertyName, propertyType] : appContext.animationController.getStory().metadata.particleProperties)
    {
      // Omit position vector
      if (propertyType != PropertyType::Vector || propertyName == Particle::POSITION_PROPERTY)
        continue;

      auto vectorColorControl = new ColorControl{propertyName.c_str(), true, this};
      vectorColorControl->getCheckBox()->setChecked(appContext.displayController.getVectorRule(propertyName).isVisible());
      vectorColorControl->getColorButton()->setColorStrategy(appContext.displayController.getVectorRule(propertyName).getColorStrategy().get());
      // Connect checkbox callback
      connect(vectorColorControl->getCheckBox(), &QCheckBox::checkStateChanged, this, [=, &appContext](Qt::CheckState checkState)
              { 
            auto updatedRule =  appContext.displayController.getVectorRule(propertyName);
            updatedRule.setVisible(checkState != Qt::Unchecked);
            appContext.displayController.setVectorRule(propertyName, updatedRule); });
      // Connect color change callback
      connect(vectorColorControl->getColorButton(), &ColorButton::clicked, this,
              [=, this, &appContext]()
              {
                auto originalRule = appContext.displayController.getVectorRule(propertyName);
                auto colorDialog = new ColorDialog{appContext, this};
                colorDialog->setColorStrategy(originalRule.getColorStrategy().get());
                if (colorDialog->exec() == QDialog::Accepted)
                {
                  auto updatedRule = originalRule;
                  updatedRule.setColorStrategy(colorDialog->getColorStrategy());
                  appContext.displayController.setVectorRule(propertyName, updatedRule);
                }
                colorDialog->deleteLater();
              });

      // Save checkbox
      layout->addWidget(vectorColorControl);
      vectorColorControls[propertyName] = vectorColorControl;
    }
  };
  // Init vector controls once
  addVectorControls();
  // Reset vector controls on story change
  appContext.animationController.storyObservable.subscribe(this,
                                                           [=, this]()
                                                           {
                                                             // Remove widgets
                                                             for (auto [_, vectorControl] : vectorColorControls)
                                                             {
                                                               layout->removeWidget(vectorControl);
                                                               vectorControl->deleteLater();
                                                             }
                                                             // Clear map
                                                             vectorColorControls.clear();
                                                             // Reset controls
                                                             addVectorControls();
                                                           });

  // Add particle rule listener
  auto particleRuleCallback = [=](DisplayRule particleRule)
  {
    particleColorControl->getCheckBox()->setChecked(particleRule.isVisible());
    particleColorControl->getColorButton()->setColorStrategy(particleRule.getColorStrategy().get());
  };
  appContext.displayController.particleRuleObservable.subscribe(this, particleRuleCallback);

  // Add vector rules listener
  auto displayVectorsCallback = [=, this](DisplayController::VectorRules vectorRules)
  {
    for (auto [property, control] : vectorColorControls)
    {
      auto it = vectorRules.find(property);
      if (it != vectorRules.end())
      {
        control->getCheckBox()->setChecked(it->second.isVisible());
        control->getColorButton()->setColorStrategy(it->second.getColorStrategy().get());
      }
      else
      {
        control->getCheckBox()->setChecked(false);
      }
    }
  };
  appContext.displayController.vectorRulesObservable.subscribe(this, displayVectorsCallback);
}

DisplayPropertyControls::~DisplayPropertyControls()
{
  appContext.displayController.particleRuleObservable.unsubscribe(this);
  appContext.displayController.vectorRulesObservable.unsubscribe(this);
}
