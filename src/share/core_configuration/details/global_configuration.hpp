#pragma once

#include "../types.hpp"
#include <pqrs/json.hpp>

namespace krbn {
namespace core_configuration {
namespace details {
class global_configuration final {
public:
  static constexpr bool check_for_updates_on_startup_default_value = true;
  static constexpr bool show_in_menu_bar_default_value = true;
  static constexpr bool enable_notification_window_default_value = true;

  global_configuration(const global_configuration&) = delete;

  global_configuration(const nlohmann::json& json)
      : json_(json),
        check_for_updates_on_startup_(check_for_updates_on_startup_default_value),
        show_in_menu_bar_(show_in_menu_bar_default_value),
        show_profile_name_in_menu_bar_(false),
        enable_notification_window_(enable_notification_window_default_value),
        ask_for_confirmation_before_quitting(true),
        unsafe_ui_(false) {
    helper_values_.push_back(std::make_unique<configuration_json_helper::value_t<bool>>("check_for_updates_on_startup",
                                                                                        check_for_updates_on_startup_,
                                                                                        check_for_updates_on_startup_default_value));
    helper_values_.push_back(std::make_unique<configuration_json_helper::value_t<bool>>("show_in_menu_bar",
                                                                                        show_in_menu_bar_,
                                                                                        show_in_menu_bar_default_value));
    helper_values_.push_back(std::make_unique<configuration_json_helper::value_t<bool>>("enable_notification_window",
                                                                                        enable_notification_window_,
                                                                                        enable_notification_window_default_value));

    pqrs::json::requires_object(json, "json");

    for (const auto& v : helper_values_) {
      v->update_value(json);
    }

    if (auto v = pqrs::json::find<bool>(json, "show_profile_name_in_menu_bar")) {
      show_profile_name_in_menu_bar_ = *v;
    }

    if (auto v = pqrs::json::find<bool>(json, "ask_for_confirmation_before_quitting")) {
      ask_for_confirmation_before_quitting = *v;
    }

    if (auto v = pqrs::json::find<bool>(json, "unsafe_ui")) {
      unsafe_ui_ = *v;
    }
  }

  nlohmann::json to_json(void) const {
    auto j = json_;

    for (const auto& v : helper_values_) {
      v->update_json(j);
    }

    j["show_profile_name_in_menu_bar"] = show_profile_name_in_menu_bar_;
    j["ask_for_confirmation_before_quitting"] = ask_for_confirmation_before_quitting;
    j["unsafe_ui"] = unsafe_ui_;
    return j;
  }

  bool get_check_for_updates_on_startup(void) const {
    return check_for_updates_on_startup_;
  }
  void set_check_for_updates_on_startup(bool value) {
    check_for_updates_on_startup_ = value;
  }

  bool get_show_in_menu_bar(void) const {
    return show_in_menu_bar_;
  }
  void set_show_in_menu_bar(bool value) {
    show_in_menu_bar_ = value;
  }

  bool get_show_profile_name_in_menu_bar(void) const {
    return show_profile_name_in_menu_bar_;
  }
  void set_show_profile_name_in_menu_bar(bool value) {
    show_profile_name_in_menu_bar_ = value;
  }

  bool get_enable_notification_window(void) const {
    return enable_notification_window_;
  }
  void set_enable_notification_window(bool value) {
    enable_notification_window_ = value;
  }

  bool get_ask_for_confirmation_before_quitting(void) const {
    return ask_for_confirmation_before_quitting;
  }
  void set_ask_for_confirmation_before_quitting(bool value) {
    ask_for_confirmation_before_quitting = value;
  }

  bool get_unsafe_ui(void) const {
    return unsafe_ui_;
  }
  void set_unsafe_ui(bool value) {
    unsafe_ui_ = value;
  }

private:
  nlohmann::json json_;
  bool check_for_updates_on_startup_;
  bool show_in_menu_bar_;
  bool show_profile_name_in_menu_bar_;
  bool enable_notification_window_;
  bool ask_for_confirmation_before_quitting;
  bool unsafe_ui_;
  std::vector<std::unique_ptr<configuration_json_helper::value_base>> helper_values_;
};

inline void to_json(nlohmann::json& json, const global_configuration& global_configuration) {
  json = global_configuration.to_json();
}
} // namespace details
} // namespace core_configuration
} // namespace krbn
