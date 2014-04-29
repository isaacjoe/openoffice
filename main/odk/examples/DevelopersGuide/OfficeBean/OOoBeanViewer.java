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



package com.sun.star.comp.beans;

import javax.swing.filechooser.*;
import javax.swing.*;
import java.io.*;

/** A simple Applet that contains the SimpleBean.
 *
 * This applet is a sample implementation of the 
 * OpenOffice.org bean. 
 * When initially loaded the applet has two buttons
 * one for opening an existent file and one to open 
 * a blank document of a given type supported by
 * OpenOffice.org eg. Writer, Calc, Impress, .....
 *
 */
 
public class OOoBeanViewer extends java.applet.Applet
{
   
   /**
    * Private variables declaration - GUI components
    */
   private java.awt.Panel rightPanel;
   private java.awt.Panel bottomPanel;
   private javax.swing.JButton closeButton;
   private javax.swing.JButton terminateButton;
   private javax.swing.JButton newDocumentButton;
   private javax.swing.JPopupMenu documentTypePopUp;
   private javax.swing.JCheckBox menuBarButton;
   private javax.swing.JCheckBox mainBarButton;
   private javax.swing.JCheckBox toolBarButton;
   private javax.swing.JCheckBox statusBarButton;
   private javax.swing.JButton storeDocumentButton;
   private javax.swing.JButton loadDocumentButton;
   private javax.swing.JButton syswinButton;
   private JTextField documentURLTextField;
   private JMenuItem item;
   private JFileChooser fileChooser;
   private byte buffer[];

   /**
    * Private variables declaration - SimpleBean variables
    */
   private OOoBean aBean;

   /**
    * Initialize the Appplet
    */
   public void init()
   {
		//The aBean needs to be initialized to add it to the applet
		aBean = new OOoBean(); 
       
        //Initialize GUI components
        rightPanel = new java.awt.Panel();
        bottomPanel = new java.awt.Panel();
        closeButton = new javax.swing.JButton("close");
        terminateButton = new javax.swing.JButton("terminate");
        newDocumentButton = new javax.swing.JButton("new document...");
        documentTypePopUp = new javax.swing.JPopupMenu();
        storeDocumentButton = new javax.swing.JButton("store to buffer");
        loadDocumentButton = new javax.swing.JButton("load from buffer");
        syswinButton = new javax.swing.JButton("release/acquire");

        menuBarButton = new javax.swing.JCheckBox("MenuBar");
		menuBarButton.setSelected( aBean.isMenuBarVisible() );
		
        mainBarButton = new javax.swing.JCheckBox("MainBar");
		mainBarButton.setSelected( aBean.isStandardBarVisible() );

        toolBarButton = new javax.swing.JCheckBox("ToolBar");
		toolBarButton.setSelected( aBean.isToolBarVisible() );

        statusBarButton = new javax.swing.JCheckBox("StatusBar");
		statusBarButton.setSelected( aBean.isStatusBarVisible() );

        documentURLTextField = new javax.swing.JTextField();
      
        //Set up the Popup Menu to create a blank document
        documentTypePopUp.setToolTipText("Create an empty document");
        
        item = documentTypePopUp.add("Text Document");
        item.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                createBlankDoc("private:factory/swriter", 
                    "New text document");
            }
        });

        item = documentTypePopUp.add("Presentation Document");
        item.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                createBlankDoc("private:factory/simpress", 
                    "New presentation document");
            }
        });

        item = documentTypePopUp.add("Drawing Document");
        item.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                createBlankDoc("private:factory/sdraw", 
                   "New drawing document");
            }
        });

        item = documentTypePopUp.add("Formula Document");
        item.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                createBlankDoc("private:factory/smath", 
                    "New formula document");
            }
        });

        item = documentTypePopUp.add("Spreadsheet Document");
        item.addActionListener(new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                createBlankDoc("private:factory/scalc", 
                    "New spreadsheet document");
            }
        });

        syswinButton.addActionListener(
				new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				try 
				{
					aBean.releaseSystemWindow();
					aBean.aquireSystemWindow();
				}
				catch ( com.sun.star.comp.beans.NoConnectionException aExc )
				{}
				catch ( com.sun.star.comp.beans.SystemWindowException aExc )
				{}
			}
       });

        storeDocumentButton.addActionListener(
				new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				try 
				{
					buffer = aBean.storeToByteArray( null, null );
				}
				catch ( Throwable aExc )
				{ 
					System.err.println( "storeToBuffer failed: " + aExc ); 
					aExc.printStackTrace( System.err );
				}
			}
       });

        loadDocumentButton.addActionListener(
				new java.awt.event.ActionListener()
        {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				try 
				{
					aBean.loadFromByteArray( buffer, null );
				}
				catch ( Throwable aExc )
				{ 
					System.err.println( "loadFromBuffer failed: " + aExc ); 
					aExc.printStackTrace( System.err );
				}
			}
       });

       closeButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                close();
            }
       });

       terminateButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                terminate();
            }
       });

       newDocumentButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
                documentTypePopUp.show((java.awt.Component)evt.getSource(), 0,0);
            }
       });

       menuBarButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				aBean.setMenuBarVisible( !aBean.isMenuBarVisible() );
            }
       });

       mainBarButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				aBean.setStandardBarVisible( !aBean.isStandardBarVisible() );
            }
       });

       toolBarButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				aBean.setToolBarVisible( !aBean.isToolBarVisible() );
            }
       });

       statusBarButton.addActionListener(new java.awt.event.ActionListener()
       {
            public void actionPerformed(java.awt.event.ActionEvent evt)
            {
				aBean.setStatusBarVisible( !aBean.isStatusBarVisible() );
            }
       });

       documentURLTextField.setEditable(false);
       documentURLTextField.setPreferredSize(new java.awt.Dimension(200, 30));

       rightPanel.setLayout( new java.awt.GridLayout(10,1) );
       rightPanel.add(closeButton);
       rightPanel.add(terminateButton);
       rightPanel.add(newDocumentButton);
       rightPanel.add(storeDocumentButton);
       rightPanel.add(loadDocumentButton);
       rightPanel.add(syswinButton);
       rightPanel.add(menuBarButton);
       rightPanel.add(mainBarButton);
       rightPanel.add(toolBarButton);
       rightPanel.add(statusBarButton);

       //bottomPanel.setLayout( new java.awt.GridLayout(1,1) );
       bottomPanel.setLayout( new java.awt.BorderLayout() );
       bottomPanel.add(documentURLTextField);

       setLayout(new java.awt.BorderLayout());

       add(aBean, java.awt.BorderLayout.CENTER);
       add(rightPanel, java.awt.BorderLayout.EAST);
       add(bottomPanel, java.awt.BorderLayout.SOUTH);
   }

   /**
    * Create a blank document of type <code>desc</code>
    *
    * @param url The private internal URL of the OpenOffice.org
    *            document describing the document
    * @param desc A description of the document to be created
    */
   private void createBlankDoc(String url, String desc)
   {
		//Create a blank document
		try
		{
            documentURLTextField.setText(desc);
            //Get the office process to load the URL
            aBean.loadFromURL( url, null );

	   		aBean.aquireSystemWindow(); 
		}
		catch ( com.sun.star.comp.beans.SystemWindowException aExc )
      	{
			System.err.println( "OOoBeanViewer.1:" );
   			aExc.printStackTrace();
		}
		catch ( com.sun.star.comp.beans.NoConnectionException aExc )
		{
			System.err.println( "OOoBeanViewer.2:" );
			aExc.printStackTrace();
		}
		catch ( Exception aExc )
		{
			System.err.println( "OOoBeanViewer.3:" );
			aExc.printStackTrace();
			//return;
		}
    }

	/** closes the bean viewer, leaves OOo running.
	 */
   private void close()
   {
			setVisible(false);
			aBean.stopOOoConnection(); 
			stop();
			System.exit(0);
   }

	/** closes the bean viewer and tries to terminate OOo.
	 */
   private void terminate()
   {
			setVisible(false);
			com.sun.star.frame.XDesktop xDesktop = null;
			try {
				xDesktop = aBean.getOOoDesktop();
			}
			catch ( com.sun.star.comp.beans.NoConnectionException aExc ) {} // ignore
			aBean.stopOOoConnection(); 
			stop();
			if ( xDesktop != null )
				xDesktop.terminate();
			System.exit(0);
   }

   /**
    * An ExitListener listening for windowClosing events
    */
   private class ExitListener extends java.awt.event.WindowAdapter
   {
        /**
         * windowClosed
         * 
         * @param e A WindowEvent for a closed Window event
         */
        public void windowClosed( java.awt.event.WindowEvent e)
        {
			close();
        }

        /**
         * windowClosing for a closing window event
         *
         * @param e A WindowEvent for a closing window event
         */
        public void windowClosing( java.awt.event.WindowEvent e)
        {
            ((java.awt.Window)e.getSource()).dispose();
        }
   }

   public static void main(String args[])
   {
       java.awt.Frame frame = new java.awt.Frame("OpenOffice.org Demo");
       OOoBeanViewer aViewer = new OOoBeanViewer();

       frame.setLayout(new java.awt.BorderLayout());

       frame.addWindowListener( aViewer.new ExitListener() );

       aViewer.init();
       aViewer.start();

       frame.add(aViewer);
       frame.setLocation( 200, 200 );
       frame.setSize( 800, 480 );
       frame.show();
   }
}

