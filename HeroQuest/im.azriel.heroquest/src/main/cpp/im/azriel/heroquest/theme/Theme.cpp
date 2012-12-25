/*
 * Theme.cpp
 *
 *  Created on: 4/12/2012
 *      Author: Azriel
 */

#include "im/azriel/heroquest/theme/Theme.h"

namespace im {
namespace azriel {
namespace heroquest {
namespace theme {

const string Theme::DEFAULT_THEME_BASE_DIR = "themes/default/";

const Theme::Image* const Theme::Image::CHAR_SELECT_COUNTDOWN = new Image("character-select/countdown.png");
const Theme::Image* const Theme::Image::CHAR_SELECT_INACTIVE_WIDGET = new Image("character-select/inactive-widget.png");
const Theme::Image* const Theme::Image::CHAR_SELECT_NO_TEAM = new Image("character-select/no-team.png");
const Theme::Image* const Theme::Image::CHAR_SELECT_PRESS_TO_JOIN = new Image("character-select/press-to-join.png");
const Theme::Image* const Theme::Image::CHAR_SELECT_RANDOM_PORTRAIT = new Image("character-select/random-portrait.png");
const Theme::Image* const Theme::Image::CHAR_SELECT_TEAM_WIDGET = new Image("character-select/team-widgets.png");
const Theme::Image* const Theme::Image::COMMON_DIALOG_SMALL = new Image("common/dialog-small.png");
const Theme::Image* const Theme::Image::MAIN_CONTROLS = new Image("main/controls.png");
const Theme::Image* const Theme::Image::MAIN_NETWORK = new Image("main/network.png");
const Theme::Image* const Theme::Image::MAIN_START = new Image("main/start.png");
const Theme::Image* const Theme::Image::TEXT = new Image("common/text.png");

Theme::Theme() : baseDir(DEFAULT_THEME_BASE_DIR) {
}

Theme::Theme(const string baseDir) : baseDir(baseDir) {
}

Theme::~Theme() {

}

const string Theme::getBaseDir() const {
	return this->baseDir;
}

const string Theme::getPathForImage(const Image* const image) const {
	return this->baseDir + image->getPath();
}

Theme::Image::Image(const string path) : path(path) {
}

Theme::Image::~Image() {
}

const string Theme::Image::getPath() const {
	return this->path;
}

} /* namespace theme */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */
