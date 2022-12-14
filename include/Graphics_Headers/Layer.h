#ifndef LAYER_H
#define LAYER_H

class Layer 
{

public:
Layer();
~Layer();

private:

virtual void OnLayerInit();
virtual void OnLayerDestroy();
virtual void OnLayerUpdate();

}



#endif 
