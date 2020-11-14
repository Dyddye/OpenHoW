/* OpenHoW
 * Copyright (C) 2017-2020 TalonBrave.info and Others (see CONTRIBUTORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define ED_DEFAULT_WINDOW_FLAGS ImGuiWindowFlags_NoSavedSettings

struct ImVec2;

class BaseWindow {
public:
    explicit BaseWindow(BaseWindow *parent = nullptr, bool status = true) {
        static unsigned int windows_id_counter = 0;
        id_ = windows_id_counter++;
        status_ = status;
        parent_ = parent;
    }

    virtual ~BaseWindow() = default;

    virtual void Display() = 0;

    bool GetStatus() { return status_; }

    void SetStatus(bool status) { status_ = status; }

    void Begin( const std::string &windowTitle, unsigned int flags );

    virtual void ToggleFullscreen();
    bool IsFullscreen() const { return isFullscreen; }

    void ToggleStatus() {
        status_ = !status_;
    }

protected:
    bool status_;
    unsigned int id_;

    BaseWindow *parent_{nullptr};

private:
	bool isFullscreen{ false };
	PLVector2 curWindowSize, curWindowPosition;
	PLVector2 oldSize, oldPosition;
};

#define dname(a)  std::string( a + "##" + /* std::to_string((ptrdiff_t)(this))*/ std::to_string(id_)).c_str()
