/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef SVTOOLS_IN_EDITBROWSEBOX_HXX
#error "not to be included directly!"
#endif

//----------------------------------------------------------------------
template <class EDIT>
GenericEditImplementation< EDIT >::GenericEditImplementation( EDIT& _rEdit )
    :m_rEdit( _rEdit )
{
}

//----------------------------------------------------------------------
template <class EDIT>
Control& GenericEditImplementation< EDIT >::GetControl()
{
    return m_rEdit;
}

//----------------------------------------------------------------------
template <class EDIT>
String GenericEditImplementation< EDIT >::GetText( LineEnd ) const
{
    // ignore the line end - this base implementation does not support it
    return m_rEdit.GetText( );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetText( const String& _rStr )
{
    m_rEdit.SetText( _rStr );
}

//----------------------------------------------------------------------
template <class EDIT>
Selection GenericEditImplementation< EDIT >::GetSelection() const
{
    return m_rEdit.GetSelection( );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetSelection( const Selection& _rSelection )
{
    m_rEdit.SetSelection( _rSelection );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetReadOnly( sal_Bool bReadOnly )
{
    m_rEdit.SetReadOnly( bReadOnly );
}

//----------------------------------------------------------------------
template <class EDIT>
sal_Bool GenericEditImplementation< EDIT >::IsReadOnly() const
{
    return m_rEdit.IsReadOnly();
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::ReplaceSelected( const String& _rStr )
{
    m_rEdit.ReplaceSelected( _rStr );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::DeleteSelected()
{
    m_rEdit.DeleteSelected();
}

//----------------------------------------------------------------------
template <class EDIT>
String GenericEditImplementation< EDIT >::GetSelected( LineEnd ) const
{
    return m_rEdit.GetSelected( );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetMaxTextLen( xub_StrLen _nMaxLen )
{
    m_rEdit.SetMaxTextLen( _nMaxLen );
}

//----------------------------------------------------------------------
template <class EDIT>
xub_StrLen GenericEditImplementation< EDIT >::GetMaxTextLen() const
{
    return (xub_StrLen)m_rEdit.GetMaxTextLen( );
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetModified()
{
    m_rEdit.SetModifyFlag();
}

//----------------------------------------------------------------------
template <class EDIT>
sal_Bool GenericEditImplementation< EDIT >::IsModified() const
{
    return m_rEdit.IsModified();
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::ClearModified()
{
    m_rEdit.ClearModifyFlag();
}

//----------------------------------------------------------------------
template <class EDIT>
void GenericEditImplementation< EDIT >::SetModifyHdl( const Link& _rLink )
{
    m_rEdit.SetModifyHdl( _rLink );
}

