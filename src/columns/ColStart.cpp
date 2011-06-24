////////////////////////////////////////////////////////////////////////////////
// taskwarrior - a command line task list manager.
//
// Copyright 2006 - 2011, Paul Beckingham, Federico Hernandez.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the
//
//     Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor,
//     Boston, MA
//     02110-1301
//     USA
//
////////////////////////////////////////////////////////////////////////////////

#define L10N                                           // Localization complete.

#include <Context.h>
#include <ColStart.h>
#include <text.h>
#include <i18n.h>

extern Context context;

////////////////////////////////////////////////////////////////////////////////
ColumnStart::ColumnStart ()
{
  _name  = "start";
  _label = STRING_COLUMN_LABEL_STARTED;
}

////////////////////////////////////////////////////////////////////////////////
ColumnStart::~ColumnStart ()
{
}

////////////////////////////////////////////////////////////////////////////////
bool ColumnStart::validate (std::string& value)
{
  return ColumnDate::validate (value);
}

////////////////////////////////////////////////////////////////////////////////
// Overriden so that style <----> label are linked.
// Note that you can not determine which gets called first.
void ColumnStart::setStyle (const std::string& value)
{
  _style = value;

  if (_style == "active" && _label == STRING_COLUMN_LABEL_STARTED)
    _label = STRING_COLUMN_LABEL_ACTIVE;
}

////////////////////////////////////////////////////////////////////////////////
// Set the minimum and maximum widths for the value.
void ColumnStart::measure (Task& task, int& minimum, int& maximum)
{
  minimum = maximum = 0;

  if (task.has (_name))
  {
    if (_style == "active")
    {
      if (! task.has ("end"))
        minimum = maximum = context.config.get ("active.indicator").length ();
    }
    else
      ColumnDate::measure (task, minimum, maximum);
  }
}

////////////////////////////////////////////////////////////////////////////////
void ColumnStart::render (
  std::vector <std::string>& lines,
  Task& task,
  int width,
  Color& color)
{
  if (task.has (_name))
  {
    if (_style == "active")
    {
      if (! task.has ("end"))
        lines.push_back (
          color.colorize (
            rightJustify (
              context.config.get ("active.indicator"), width)));
    }
    else
      ColumnDate::render (lines, task, width, color);
  }
}

////////////////////////////////////////////////////////////////////////////////
