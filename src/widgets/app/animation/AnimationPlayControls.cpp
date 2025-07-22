#include "AnimationPlayControls.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

AnimationPlayControls::AnimationPlayControls(AppContext &appContext, QWidget *parent) : appContext{appContext}, Section{parent}
{
  // Create play button
  auto playButton = new QPushButton{this};
  playButton->setCheckable(true);
  connect(playButton, &QPushButton::clicked, this,
          [&appContext](bool checked)
          {
            if (checked)
              appContext.animationController.play();
            else
              appContext.animationController.pause();
          });

  // Create rewind button
  auto rewindButton = new QPushButton{"Retroceder", this};
  connect(rewindButton, &QPushButton::clicked, this,
          [&appContext]()
          {
            appContext.animationController.rewind();
          });

  // Create forward button
  auto forwardButton = new QPushButton{"Avanzar", this};
  connect(forwardButton, &QPushButton::clicked, this,
          [&appContext]()
          {
            appContext.animationController.skip();
          });

  // Build layout
  auto layout = new QHBoxLayout{content};
  layout->addWidget(rewindButton);
  layout->addWidget(playButton);
  layout->addWidget(forwardButton);
  layout->setAlignment(Qt::AlignCenter);
  layout->setContentsMargins({});

  // Add animation playing listener
  auto playingCallback = [=](bool playing)
  {
    if (playing)
    {
      playButton->setText("Pausa");
      playButton->setChecked(true);
    }
    else
    {
      playButton->setText("Inicio");
      playButton->setChecked(false);
    }
  };
  appContext.animationController.playingObservable.subscribe(this, playingCallback, true);
}

AnimationPlayControls::~AnimationPlayControls()
{
  appContext.animationController.playingObservable.unsubscribe(this);
}