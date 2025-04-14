#include <raylib.h>
#include <vector>

enum class StepType {
    HIGHLIGHT_NODE,
    DRAW_EDGE_PROGRESS,
    ADD_NODE_OBJECT,
    ADD_EDGE_OBJECT,

};


struct AnimationStep {
    StepType type;      
    float duration = 0.f;   

   
    int nodeId = -1;    
    int fromNode = -1;  
    int toNode = -1;
    float progress = 0.f; 

 
};


std::vector<AnimationStep> createAddEdgeSteps(int from, int to) {
    std::vector<AnimationStep> steps;

    // Step 1: Highlight node 'from'

    AnimationStep s1;
    s1.type = StepType::HIGHLIGHT_NODE;
    s1.nodeId = from;
    s1.duration = 0.5f; 
    steps.push_back(s1);

    // Step 2: Highlight node 'to'
    AnimationStep s2;
    s2.type = StepType::HIGHLIGHT_NODE;
    s2.nodeId = to;
    s2.duration = 0.5f;
    steps.push_back(s2);

    // Step 3: draw line
    AnimationStep s3;
    s3.type = StepType::DRAW_EDGE_PROGRESS;
    s3.fromNode = from;
    s3.toNode = to;
    s3.progress = 0.f;   
    s3.duration = 1.0f;  
    steps.push_back(s3);

    
    AnimationStep s4;
    s4.type = StepType::ADD_EDGE_OBJECT;
    s4.fromNode = from;
    s4.toNode = to;
    s4.duration = 0.2f;   
    steps.push_back(s4);

    return steps;
}
