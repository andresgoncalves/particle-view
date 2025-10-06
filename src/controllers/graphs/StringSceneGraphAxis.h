// #ifndef STRING_SCENE_GRAPH_AXIS_H
// #define STRING_SCENE_GRAPH_AXIS_H

// #include "GraphAxis.h"

// /** Graph a string property */
// class StringSceneGraphAxis : public GraphAxis<std::string>
// {
// public:
//   StringSceneGraphAxis(std::string propertyName)
//       : GraphAxis{}, propertyName{propertyName}
//   {
//   }

//   /** Get scene value with current axis */
//   std::optional<std::string> getValue(const Scene &scene) const override
//   {
//     auto property = scene.getProperty(propertyName);
//     if (!property.has_value() || property.value().getType() != PropertyType::String)
//       return std::nullopt;
//     return property.value().getValue<PropertyType::String>()->value;
//   }

//   /** Get axis text */
//   std::string getText() const override
//   {
//     return propertyName;
//   }

//   /** Get property name */
//   std::string getPropertyName() const
//   {
//     return propertyName;
//   }

// private:
//   std::string propertyName;
// };

// #endif