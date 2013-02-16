/*
 * Theme.h
 *
 *  Created on: 4/12/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_HEROQUEST_THEME__THEME_H_
#define __IM_AZRIEL_HEROQUEST_THEME__THEME_H_

#include <map>
#include <string>

using namespace std;

namespace im {
namespace azriel {
namespace heroquest {
namespace theme {

class Theme {
public:

	static constexpr int TEXT_WIDTH = 10;
	static constexpr int TEXT_HEIGHT = 18;

	/**
	 * Constants that for each image
	 */
	class Image {
	public:
		/**
		 * Constant for the character selection menu count down image sheet
		 */
		static const Image* const CHAR_SELECT_COUNTDOWN;
		/**
		 * Constant for the character selection menu inactive widget image sheet
		 */
		static const Image* const CHAR_SELECT_INACTIVE_WIDGET;
		/**
		 * Constant for the character selection menu image sheet
		 */
		static const Image* const CHAR_SELECT_NO_TEAM;
		static const Image* const CHAR_SELECT_PRESS_TO_JOIN;
		static const Image* const CHAR_SELECT_RANDOM_PORTRAIT;
		static const Image* const CHAR_SELECT_TEAM_WIDGET;
		static const Image* const COMMON_DIALOG_SMALL;
		static const Image* const MAIN_CONTROLS;
		static const Image* const MAIN_NETWORK;
		static const Image* const MAIN_START;
		static const Image* const TEXT;

	private:
		const string path;

	public:
		const string getPath() const;

	private:
		Image(const string path);
		virtual ~Image();
	};

protected:
	/**
	 * The default base directory for a theme ("themes/default/").
	 */
	static const string DEFAULT_THEME_BASE_DIR;

	/**
	 * The base directory of the images for this theme.
	 */
	const string baseDir;

public:
	/**
	 * Create a theme with the default theme base directory ("themes/default/").
	 */
	Theme();
	/**
	 * Create a theme using the specified directory as the base directory for the theme. The path must end with a
	 * trailing backslash, e.g. "themes/mytheme/";
	 *
	 * @param baseDir the base directory of the theme to use
	 */
	Theme(const string baseDir);
	virtual ~Theme();

	/**
	 * Get the base directory of this theme
	 *
	 * @return the base directory of this theme
	 */
	const string getBaseDir() const;
	/**
	 * Get the path to one of the theme's images.
	 *
	 * @param image the image to retrieve the path for
	 *
	 * @return the path of the image
	 */
	const string getPathForImage(const Image* const image) const;
};

} /* namespace theme */
} /* namespace heroquest */
} /* namespace azriel */
} /* namespace im */

#endif /* __IM_AZRIEL_HEROQUEST_THEME__THEME_H_ */
