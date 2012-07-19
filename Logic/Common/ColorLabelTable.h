/*=========================================================================

  Program:   ITK-SNAP
  Module:    $RCSfile: ColorLabelTable.h,v $
  Language:  C++
  Date:      $Date: 2009/10/26 22:18:03 $
  Version:   $Revision: 1.5 $
  Copyright (c) 2007 Paul A. Yushkevich
  
  This file is part of ITK-SNAP 

  ITK-SNAP is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  -----

  Copyright (c) 2003 Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information. 

=========================================================================*/
#ifndef __ColorLabelTable_h_
#define __ColorLabelTable_h_

#include "Registry.h"
#include "ColorLabel.h"
#include "itkExceptionObject.h"

/**
 * \class ColorLabelTable
 * \brief A table for managing color labels
 * TODO: rewrite this class using std::map, current implementation is
 * horribly inefficient
 */
class ColorLabelTable
{
public:
  ColorLabelTable();

  // Flat file IO
  void LoadFromFile(const char *file) throw(itk::ExceptionObject);
  void SaveToFile(const char *file) throw(itk::ExceptionObject);

  // Registry IO
  void LoadFromRegistry(Registry &registry);
  void SaveToRegistry(Registry &registry);

  /** Initialize the labels to a default state */
  void InitializeToDefaults();

  /** Clear all the color labels, except the 'clear' label */
  void RemoveAllLabels();

  /** Get the number of valid color labels */
  size_t GetNumberOfValidLabels();

  /** Get the first valid non-zero color label (or zero if there are none)  */
  LabelType GetFirstValidLabel() const;

  /**
    Get the color label corresponding to the given value. If the requested
    label is not valid, a default value is returned
  */
  const ColorLabel GetColorLabel(size_t id) const;

  /** Set the i'th color label, i between 0 and 255 */
  void SetColorLabel(size_t id, const ColorLabel &label);

  /** Generate a default color label at index i */
  ColorLabel GetDefaultColorLabel(LabelType id) const;

  bool IsColorLabelValid(LabelType id) const;

  /** Sets the color label valid or invalid. During invalidation, the label
   * reverts to default values */
  void SetColorLabelValid(LabelType id, bool flag);

  // Map between valid label IDS and label descriptors
  typedef std::map<LabelType, ColorLabel> ValidLabelMap;
  typedef ValidLabelMap::const_iterator ValidLabelConstIterator;

  /** Get the iterator over the valid labels */
  ValidLabelConstIterator begin() const { return m_LabelMap.begin(); }
  ValidLabelConstIterator end() const { return m_LabelMap.end(); }

  /** Get the collection of defined/valid labels */
  const ValidLabelMap &GetValidLabels() const { return m_LabelMap; }

private:

  // The main data array
  ValidLabelMap m_LabelMap;

  // A flat array of color labels
  // ColorLabel m_Label[MAX_COLOR_LABELS], m_DefaultLabel[MAX_COLOR_LABELS];

  static const char *m_ColorList[];
  static const size_t m_ColorListSize;
};

#endif
