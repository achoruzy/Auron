#ifndef STEP_HANDLER_H
#define STEP_HANDLER_H

#include <string>
#include <vector>
#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
#include <BRep_Tool.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <Poly_Triangulation.hxx>
#include <TopExp_Explorer.hxx>
#include <TopAbs.hxx>
#include <TopLoc_Location.hxx>
#include <Geom_Plane.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepTools.hxx>
#include <gp_Pln.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>

class STEPHandler {
public:
    STEPHandler();
    ~STEPHandler();

    // Load a STEP file and process its data
    bool loadSTEPFile(const std::string& filePath);

    // Retrieve the processed vertices
    const std::vector<float>& getVertices() const;

    // Retrieve the processed indices
    const std::vector<int>& getIndices() const;

    // Perform mathematical intersection with a given plane
    bool intersectWithPlane(const gp_Pln& plane);

    // Retrieve intersection vertices for visualization
    const std::vector<float>& getIntersectionVertices() const;

private:
    // Internal data structure to store model data
    struct ModelData {
        std::vector<float> vertices;
        std::vector<int> indices;
    };

    ModelData modelData;

    // Intersection data
    std::vector<float> intersectionVertices;

    // Helper function to reset model data
    void resetModelData();

    // Helper function to reset intersection data
    void resetIntersectionData();
};

STEPHandler::STEPHandler() {
    resetModelData();
    resetIntersectionData();
}

STEPHandler::~STEPHandler() {
    // Cleanup if necessary
}

bool STEPHandler::loadSTEPFile(const std::string& filePath) {
    STEPControl_Reader reader;
    if (reader.ReadFile(filePath.c_str()) != IFSelect_RetDone) {
        return false; // Failed to read STEP file
    }

    reader.TransferRoots();
    TopoDS_Shape shape = reader.OneShape();

    // Generate mesh for the shape
    BRepMesh_IncrementalMesh mesh(shape, 0.1);
    if (!mesh.IsDone()) {
        return false; // Failed to generate mesh
    }

    resetModelData();

    // Extract triangulation data
    for (TopExp_Explorer exp(shape, TopAbs_FACE); exp.More(); exp.Next()) {
        TopoDS_Face face = TopoDS::Face(exp.Current());
        TopLoc_Location loc;
        Handle(Poly_Triangulation) triangulation = BRep_Tool::Triangulation(face, loc);
        if (!triangulation.IsNull()) {
            const TColgp_Array1OfPnt& nodes = triangulation->Nodes();
            const Poly_Array1OfTriangle& triangles = triangulation->Triangles();

            // Add vertices
            for (int i = nodes.Lower(); i <= nodes.Upper(); ++i) {
                gp_Pnt p = nodes(i);
                modelData.vertices.push_back(static_cast<float>(p.X()));
                modelData.vertices.push_back(static_cast<float>(p.Y()));
                modelData.vertices.push_back(static_cast<float>(p.Z()));
            }

            // Add indices
            for (int i = triangles.Lower(); i <= triangles.Upper(); ++i) {
                int n1, n2, n3;
                triangles(i).Get(n1, n2, n3);
                modelData.indices.push_back(n1 - 1); // Convert 1-based to 0-based index
                modelData.indices.push_back(n2 - 1);
                modelData.indices.push_back(n3 - 1);
            }
        }
    }

    return true;
}

const std::vector<float>& STEPHandler::getVertices() const {
    return modelData.vertices;
}

const std::vector<int>& STEPHandler::getIndices() const {
    return modelData.indices;
}

bool STEPHandler::intersectWithPlane(const gp_Pln& plane) {
    resetIntersectionData();

    // Create a face from the plane
    TopoDS_Face planeFace = BRepBuilderAPI_MakeFace(plane, -1000, 1000, -1000, 1000);

    // Perform intersection
    BRepAlgoAPI_Section section(modelData.shape, planeFace, Standard_False);
    section.ComputePCurveOn1(Standard_True);
    section.Approximation(Standard_True);
    section.Build();

    if (!section.IsDone()) {
        return false; // Intersection failed
    }

    // Extract intersection edges
    TopoDS_Shape result = section.Shape();
    for (TopExp_Explorer exp(result, TopAbs_EDGE); exp.More(); exp.Next()) {
        TopoDS_Edge edge = TopoDS::Edge(exp.Current());
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, loc, first, last);
        if (!curve.IsNull()) {
            // Sample points along the curve for visualization
            for (Standard_Real t = first; t <= last; t += 0.1) {
                gp_Pnt p;
                curve->D0(t, p);
                intersectionVertices.push_back(static_cast<float>(p.X()));
                intersectionVertices.push_back(static_cast<float>(p.Y()));
                intersectionVertices.push_back(static_cast<float>(p.Z()));
            }
        }
    }

    return true;
}

const std::vector<float>& STEPHandler::getIntersectionVertices() const {
    return intersectionVertices;
}

void STEPHandler::resetModelData() {
    modelData.vertices.clear();
    modelData.indices.clear();
}

void STEPHandler::resetIntersectionData() {
    intersectionVertices.clear();
}

#endif // STEP_HANDLER_H