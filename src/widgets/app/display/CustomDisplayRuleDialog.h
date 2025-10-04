#ifndef CUSTOM_DISPLAY_RULE_DIALOG_H
#define CUSTOM_DISPLAY_RULE_DIALOG_H

#include <optional>

#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QComboBox>

#include <controllers/AppContext.h>
#include <widgets/shared/buttons/ColorButton.h>
#include <widgets/shared/controls/TextControl.h>
#include <widgets/shared/controls/NumericControl.h>
#include <widgets/shared/controls/matcher/ParticleMatcherControl.h>

class CustomDisplayRuleDialog : public QDialog
{
public:
  CustomDisplayRuleDialog(AppContext &appContext, QWidget *parent = nullptr);
  CustomDisplayRuleDialog(const DisplayRule &displayRule, AppContext &appContext, QWidget *parent = nullptr);

  DisplayRule getDisplayRule() const;

private:
  CustomDisplayRuleDialog(bool edit, AppContext &appContext, QWidget *parent = nullptr);

  std::optional<DisplayRule> originalDisplayRule;

  ParticleMatcherControl *particleMatcherControl;
  ColorButton *colorButton;
  QColor selectedColor;
};

#endif