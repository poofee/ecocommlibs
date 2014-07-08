// $Header: //depot/release/ironman2012/develop/global/inc/dbxsdk/AcDbAssocCompoundActionParam.h#1 $ 
// $Change: 237375 $ $DateTime: 2011/01/30 18:32:54 $ $Author: integrat $
//
//////////////////////////////////////////////////////////////////////////////
//
// Copyright � 2009-2010 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
// CREATED BY: Jiri Kripac                                 March 2009
//
// DESCRIPTION:
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "AcDbAssocActionParam.h"
#pragma pack (push, 8)


/// <summary>
/// Action parameter that owns other AcDbAssocActionParameters, allowing to represent 
/// hierarchical structures of action parameters.
/// </summary>
///
class ACDB_PORT AcDbAssocCompoundActionParam : public AcDbAssocActionParam
{
public:
    ACRX_DECLARE_MEMBERS(AcDbAssocCompoundActionParam);

    /// <summary> Default constructor. </summary>
    /// <param name="createImpObject"> See AcDbAssocCreateImpObject. </param>
    ///
    explicit AcDbAssocCompoundActionParam(AcDbAssocCreateImpObject createImpObject = kAcDbAssocCreateImpObject);

    /// <summary> 
    /// Removes all owned AcDbAssocActionParams, optionally also erasing them. 
    /// </summary>
    /// <param name="alsoEraseThem">  
    /// If true, the owned AcDbAssocActionParams are also erased. Otherwise they
    /// are just detached so that this AcDbAssocCompoundActionParam is not their
    /// database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    virtual Acad::ErrorStatus removeAllParams(bool alsoEraseThem);

    /// <summary> Returns then number of the owned AcDbAssocActionParams. </summary>
    /// <returns> Number of the owned AcDbAssocActionParams. </returns>
    ///
    int paramCount() const;

    /// <summary> 
    /// Returns an array of the owned AcDbAssocActionParams. 
    /// </summary>
    /// <returns> 
    /// Array of the owned AcDbAssocActionParams. Notice that it returns a 
    /// const reference to an internal array. The client code must not hold on 
    /// to this array and should make a copy of the array if it is doing anything 
    /// more than just momentarily accessing its elements.
    /// </returns>
    ///
    const AcDbObjectIdArray& ownedParams() const;

    /// <summary> 
    /// Adds a new AcDbAssocActionParam. The AcDbAssocCompoundActionParam
    /// becomes the database owner of this action parameter.
    /// </summary>
    /// <param name="paramId"> 
    /// AcDbObjectId of the action parameter being added. If the action parameter 
    /// is already owned by this AcDbAssocCompoundActionParam, it it just returns 
    /// its existing index in the array and does not add it again. 
    ///</param>
    /// <param name="paramIndex"> 
    /// Returned index of the newly added action parameter. If the parameter is 
    /// already owned by this AcDbAssocCompoundActionParam, its existing index
    /// is returned.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus addParam(const AcDbObjectId& paramId, int& paramIndex);

    /// <summary> 
    /// Removes the AcDbAssocActionParam, optionally also erasing it. 
    /// </summary>
    /// <param name="paramId"> AcDbObjectId of the action parameter to remove. </param>
    /// <param name="alsoEraseIt">  
    /// If true, the owned action parameter is also erased. Otherwise it is just
    /// detached so that this AcDbAssocCompoundActionParam is not its database owner.
    /// </param>
    /// <returns> Acad::ErrorStatus. </returns>
    ///
    Acad::ErrorStatus removeParam(const AcDbObjectId& paramId, bool alsoEraseIt); 

    /// <summary> 
    /// Returns all owned AcDbAssocActionParams with the given name. Notice that
    /// more than one action parameter may have the same name. The parameters are 
    /// always returned in the same order which is the order the parameters were 
    /// added to the action body. Thus, an array of action parameters can easily 
    /// be represented by multiple action parameters with the same name.
    /// </summary>
    /// <param name="paramName">  The name of the action parameter. </param>
    /// <returns> All owned action parameters with the given name. </returns>
    ///
    const AcDbObjectIdArray& paramsAtName(const AcString& paramName) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam specified by its name and optional 
    /// index among all parameters with the same name. The default index 0 means
    /// the first parameter with the given name is returned.
    /// </summary>
    /// <param name="paramName"> The name of the action parameter. </param>
    /// <param name="index"> Index among all parameters with the same name. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtName(const AcString& paramName, int index = 0) const;

    /// <summary> 
    /// Returns an owned AcDbAssocActionParam in the array of all action parameters 
    /// owned by this AcDbAssocCompoundActionParam.
    /// </summary>
    /// <param name="paramIndex"> Index in the array of all action parameters. </param>
    /// <returns> The owned action parameter or a null AcDbObjectId if not found. </returns>
    ///
    AcDbObjectId paramAtIndex(int paramIndex) const;
};

#pragma pack (pop)