/**CFile****************************************************************

  FileName    [ivyShow.c]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [And-Inverter Graph package.]

  Synopsis    [Visualization of HAIG.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - May 11, 2006.]

  Revision    [$Id: ivyShow.c,v 1.00 2006/05/11 00:00:00 alanmi Exp $]

***********************************************************************/

#include "aig.h"

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Writes the graph structure of AIG for DOT.]

  Description [Useful for graph visualization using tools such as GraphViz: 
  http://www.graphviz.org/]
  
  SideEffects []

  SeeAlso     []

***********************************************************************/
void Aig_WriteDotAig( Aig_Man_t * pMan, char * pFileName, int fHaig, Vec_Ptr_t * vBold )
{
    FILE * pFile;
    Aig_Obj_t * pNode;//, * pTemp, * pPrev;
    int LevelMax, Level, i;

    if ( Aig_ManNodeNum(pMan) > 200 )
    {
        fprintf( stdout, "Cannot visualize AIG with more than 200 nodes.\n" );
        return;
    }
    if ( (pFile = fopen( pFileName, "w" )) == NULL )
    {
        fprintf( stdout, "Cannot open the intermediate file \"%s\".\n", pFileName );
        return;
    }

    // mark the nodes
    if ( vBold )
        Vec_PtrForEachEntry( vBold, pNode, i )
            pNode->fMarkB = 1;

    // compute levels
//    LevelMax = 1 + Aig_ManSetLevels( pMan, fHaig );
    LevelMax = 1 + Aig_ManLevels( pMan );
    Aig_ManForEachPo( pMan, pNode, i )
        pNode->Level = LevelMax;

    // write the DOT header
    fprintf( pFile, "# %s\n",  "AIG structure generated by IVY package" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "digraph AIG {\n" );
    fprintf( pFile, "size = \"7.5,10\";\n" );
//  fprintf( pFile, "ranksep = 0.5;\n" );
//  fprintf( pFile, "nodesep = 0.5;\n" );
    fprintf( pFile, "center = true;\n" );
//  fprintf( pFile, "orientation = landscape;\n" );
//  fprintf( pFile, "edge [fontsize = 10];\n" );
//  fprintf( pFile, "edge [dir = none];\n" );
    fprintf( pFile, "edge [dir = back];\n" );
    fprintf( pFile, "\n" );

    // labels on the left of the picture
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  node [shape = plaintext];\n" );
    fprintf( pFile, "  edge [style = invis];\n" );
    fprintf( pFile, "  LevelTitle1 [label=\"\"];\n" );
    fprintf( pFile, "  LevelTitle2 [label=\"\"];\n" );
    // generate node names with labels
    for ( Level = LevelMax; Level >= 0; Level-- )
    {
        // the visible node name
        fprintf( pFile, "  Level%d", Level );
        fprintf( pFile, " [label = " );
        // label name
        fprintf( pFile, "\"" );
        fprintf( pFile, "\"" );
        fprintf( pFile, "];\n" );
    }

    // genetate the sequence of visible/invisible nodes to mark levels
    fprintf( pFile, "  LevelTitle1 ->  LevelTitle2 ->" );
    for ( Level = LevelMax; Level >= 0; Level-- )
    {
        // the visible node name
        fprintf( pFile, "  Level%d",  Level );
        // the connector
        if ( Level != 0 )
            fprintf( pFile, " ->" );
        else
            fprintf( pFile, ";" );
    }
    fprintf( pFile, "\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate title box on top
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    fprintf( pFile, "  LevelTitle1;\n" );
    fprintf( pFile, "  title1 [shape=plaintext,\n" );
    fprintf( pFile, "          fontsize=20,\n" );
    fprintf( pFile, "          fontname = \"Times-Roman\",\n" );
    fprintf( pFile, "          label=\"" );
    fprintf( pFile, "%s", "AIG structure visualized by ABC" );
    fprintf( pFile, "\\n" );
    fprintf( pFile, "Benchmark \\\"%s\\\". ", "aig" );
//    fprintf( pFile, "Time was %s. ",  Extra_TimeStamp() );
    fprintf( pFile, "\"\n" );
    fprintf( pFile, "         ];\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate statistics box
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    fprintf( pFile, "  LevelTitle2;\n" );
    fprintf( pFile, "  title2 [shape=plaintext,\n" );
    fprintf( pFile, "          fontsize=18,\n" );
    fprintf( pFile, "          fontname = \"Times-Roman\",\n" );
    fprintf( pFile, "          label=\"" );
    fprintf( pFile, "The set contains %d logic nodes and spans %d levels.", Aig_ManNodeNum(pMan), LevelMax );
    fprintf( pFile, "\\n" );
    fprintf( pFile, "\"\n" );
    fprintf( pFile, "         ];\n" );
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate the COs
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    // the labeling node of this level
    fprintf( pFile, "  Level%d;\n",  LevelMax );
    // generate the CO nodes
    Aig_ManForEachPo( pMan, pNode, i )
    {
/*
        if ( fHaig || pNode->pEquiv == NULL )
            fprintf( pFile, "  Node%d%s [label = \"%d%s\"", pNode->Id, 
                (Aig_ObjIsLatch(pNode)? "_in":""), pNode->Id, (Aig_ObjIsLatch(pNode)? "_in":"") );
        else
            fprintf( pFile, "  Node%d%s [label = \"%d%s(%d%s)\"", pNode->Id, 
                (Aig_ObjIsLatch(pNode)? "_in":""), pNode->Id, (Aig_ObjIsLatch(pNode)? "_in":""), 
                    Aig_Regular(pNode->pEquiv)->Id, Aig_IsComplement(pNode->pEquiv)? "\'":"" );
*/
        fprintf( pFile, "  Node%d [label = \"%d\"", pNode->Id, pNode->Id ); 

        fprintf( pFile, ", shape = %s", (Aig_ObjIsLatch(pNode)? "box":"invtriangle") );
        fprintf( pFile, ", color = coral, fillcolor = coral" );
        fprintf( pFile, "];\n" );
    }
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate nodes of each rank
    for ( Level = LevelMax - 1; Level > 0; Level-- )
    {
        fprintf( pFile, "{\n" );
        fprintf( pFile, "  rank = same;\n" );
        // the labeling node of this level
        fprintf( pFile, "  Level%d;\n",  Level );
        Aig_ManForEachObj( pMan, pNode, i )
        {
            if ( (int)pNode->Level != Level )
                continue;
/*
            if ( fHaig || pNode->pEquiv == NULL )
                fprintf( pFile, "  Node%d [label = \"%d\"", pNode->Id, pNode->Id );
            else 
                fprintf( pFile, "  Node%d [label = \"%d(%d%s)\"", pNode->Id, pNode->Id, 
                    Aig_Regular(pNode->pEquiv)->Id, Aig_IsComplement(pNode->pEquiv)? "\'":"" );
*/
            fprintf( pFile, "  Node%d [label = \"%d\"", pNode->Id, pNode->Id ); 

            fprintf( pFile, ", shape = ellipse" );
            if ( vBold && pNode->fMarkB )
                fprintf( pFile, ", style = filled" );
            fprintf( pFile, "];\n" );
        }
        fprintf( pFile, "}" );
        fprintf( pFile, "\n" );
        fprintf( pFile, "\n" );
    }

    // generate the CI nodes
    fprintf( pFile, "{\n" );
    fprintf( pFile, "  rank = same;\n" );
    // the labeling node of this level
    fprintf( pFile, "  Level%d;\n",  0 );
    // generate constant node
    if ( Aig_ObjRefs(Aig_ManConst1(pMan)) > 0 )
    {
        pNode = Aig_ManConst1(pMan);
        // check if the costant node is present
        fprintf( pFile, "  Node%d [label = \"Const1\"", pNode->Id );
        fprintf( pFile, ", shape = ellipse" );
        fprintf( pFile, ", color = coral, fillcolor = coral" );
        fprintf( pFile, "];\n" );
    }
    // generate the CI nodes
    Aig_ManForEachPi( pMan, pNode, i )
    {
/*
        if ( fHaig || pNode->pEquiv == NULL )
            fprintf( pFile, "  Node%d%s [label = \"%d%s\"", pNode->Id, 
                (Aig_ObjIsLatch(pNode)? "_out":""), pNode->Id, (Aig_ObjIsLatch(pNode)? "_out":"") );
        else
            fprintf( pFile, "  Node%d%s [label = \"%d%s(%d%s)\"", pNode->Id, 
                (Aig_ObjIsLatch(pNode)? "_out":""), pNode->Id, (Aig_ObjIsLatch(pNode)? "_out":""), 
                    Aig_Regular(pNode->pEquiv)->Id, Aig_IsComplement(pNode->pEquiv)? "\'":"" );
*/
        fprintf( pFile, "  Node%d [label = \"%d\"", pNode->Id, pNode->Id ); 

        fprintf( pFile, ", shape = %s", (Aig_ObjIsLatch(pNode)? "box":"triangle") );
        fprintf( pFile, ", color = coral, fillcolor = coral" );
        fprintf( pFile, "];\n" );
    }
    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );

    // generate invisible edges from the square down
    fprintf( pFile, "title1 -> title2 [style = invis];\n" );
    Aig_ManForEachPo( pMan, pNode, i )
        fprintf( pFile, "title2 -> Node%d%s [style = invis];\n", pNode->Id, (Aig_ObjIsLatch(pNode)? "_in":"") );

    // generate edges
    Aig_ManForEachObj( pMan, pNode, i )
    {
        if ( !Aig_ObjIsNode(pNode) && !Aig_ObjIsPo(pNode) && !Aig_ObjIsBuf(pNode) )
            continue;
        // generate the edge from this node to the next
        fprintf( pFile, "Node%d%s",  pNode->Id, (Aig_ObjIsLatch(pNode)? "_in":"") );
        fprintf( pFile, " -> " );
        fprintf( pFile, "Node%d%s",  Aig_ObjFaninId0(pNode), (Aig_ObjIsLatch(Aig_ObjFanin0(pNode))? "_out":"") );
        fprintf( pFile, " [" );
        fprintf( pFile, "style = %s", Aig_ObjFaninC0(pNode)? "dotted" : "bold" );
//        if ( Aig_NtkIsSeq(pNode->pMan) && Seq_ObjFaninL0(pNode) > 0 )
//        fprintf( pFile, ", label = \"%s\"", Seq_ObjFaninGetInitPrintable(pNode,0) );
        fprintf( pFile, "]" );
        fprintf( pFile, ";\n" );
        if ( !Aig_ObjIsNode(pNode) )
            continue;
        // generate the edge from this node to the next
        fprintf( pFile, "Node%d",  pNode->Id );
        fprintf( pFile, " -> " );
        fprintf( pFile, "Node%d%s",  Aig_ObjFaninId1(pNode), (Aig_ObjIsLatch(Aig_ObjFanin1(pNode))? "_out":"") );
        fprintf( pFile, " [" );
        fprintf( pFile, "style = %s", Aig_ObjFaninC1(pNode)? "dotted" : "bold" );
//        if ( Aig_NtkIsSeq(pNode->pMan) && Seq_ObjFaninL1(pNode) > 0 )
//        fprintf( pFile, ", label = \"%s\"", Seq_ObjFaninGetInitPrintable(pNode,1) );
        fprintf( pFile, "]" );
        fprintf( pFile, ";\n" );
/*
        // generate the edges between the equivalent nodes
        if ( fHaig && pNode->pEquiv && Aig_ObjRefs(pNode) > 0 )
        {
            pPrev = pNode;
            for ( pTemp = pNode->pEquiv; pTemp != pNode; pTemp = Aig_Regular(pTemp->pEquiv) )
            {
                fprintf( pFile, "Node%d",  pPrev->Id );
                fprintf( pFile, " -> " );
                fprintf( pFile, "Node%d",  pTemp->Id );
                fprintf( pFile, " [style = %s]", Aig_IsComplement(pTemp->pEquiv)? "dotted" : "bold" );
                fprintf( pFile, ";\n" );
                pPrev = pTemp;
            }
            // connect the last node with the first
            fprintf( pFile, "Node%d",  pPrev->Id );
            fprintf( pFile, " -> " );
            fprintf( pFile, "Node%d",  pNode->Id );
            fprintf( pFile, " [style = %s]", Aig_IsComplement(pPrev->pEquiv)? "dotted" : "bold" );
            fprintf( pFile, ";\n" );
        }
*/
    }

    fprintf( pFile, "}" );
    fprintf( pFile, "\n" );
    fprintf( pFile, "\n" );
    fclose( pFile );

    // unmark nodes
    if ( vBold )
        Vec_PtrForEachEntry( vBold, pNode, i )
            pNode->fMarkB = 0;

    Aig_ManForEachPo( pMan, pNode, i )
        pNode->Level = Aig_ObjFanin0(pNode)->Level;
}

/**Function*************************************************************

  Synopsis    []

  Description []
               
  SideEffects []

  SeeAlso     []

***********************************************************************/
#if 0
void Aig_ManShow( Aig_Man_t * pMan, int fHaig, Vec_Ptr_t * vBold )
{
    extern void Abc_ShowFile( char * FileNameDot );
    static Counter = 0;
    char FileNameDot[200];
    FILE * pFile;
    // create the file name
//    Aig_ShowGetFileName( pMan->pName, FileNameDot );
    sprintf( FileNameDot, "temp%02d.dot", Counter++ );
    // check that the file can be opened
    if ( (pFile = fopen( FileNameDot, "w" )) == NULL )
    {
        fprintf( stdout, "Cannot open the intermediate file \"%s\".\n", FileNameDot );
        return;
    }
    fclose( pFile );
    // generate the file
    Aig_WriteDotAig( pMan, FileNameDot, fHaig, vBold );
    // visualize the file 
    Abc_ShowFile( FileNameDot );
}
#endif


////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////


