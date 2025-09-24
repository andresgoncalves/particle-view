#include "VectorControl.h"

#include <QtWidgets/QHBoxLayout>

VectorControl::VectorControl(QWidget *parent) : VectorControl{nullptr, {"x:", "y:", "z:"}, parent} {}

VectorControl::VectorControl(const char *title, QWidget *parent) : VectorControl{title, {"x:", "y:", "z:"}, parent} {}

VectorControl::VectorControl(std::array<const char *, 3> subtitles, QWidget *parent) : VectorControl{nullptr, subtitles, parent} {}

VectorControl::VectorControl(const char *title, std::array<const char *, 3> subtitles, QWidget *parent) : Control{title, new QWidget{}}
{
  // Build controls
  controls[0] = new NumericControl{subtitles[0], this};
  controls[1] = new NumericControl{subtitles[1], this};
  controls[2] = new NumericControl{subtitles[2], this};

  // Build layout
  auto layout = new QHBoxLayout{widget};
  layout->addWidget(controls[0]);
  layout->addWidget(controls[1]);
  layout->addWidget(controls[2]);
  layout->setContentsMargins({});
}

std::array<NumericControl *, 3> VectorControl::getControls() const
{
  return controls;
}

void VectorControl::setValue(QVector3D value)
{
  controls[0]->setValue(value.x());
  controls[1]->setValue(value.y());
  controls[2]->setValue(value.z());
}

QVector3D VectorControl::getValue() const
{
  return {
      controls[0]->getValue<float>(),
      controls[1]->getValue<float>(),
      controls[2]->getValue<float>(),
  };
}

void VectorControl::onChange(std::function<void(QVector3D)> callback) const
{
  auto changeHandler = [callback, this](float)
  {
    callback(getValue());
  };
  controls[0]->onChange<float>(changeHandler);
  controls[1]->onChange<float>(changeHandler);
  controls[2]->onChange<float>(changeHandler);
}