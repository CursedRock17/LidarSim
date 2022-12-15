#ifndef LAYER_H
#define LAYER_H

class Layer {
public:
Layer();
~Layer();

virtual void OnLayerInit();
virtual void OnLayerDestroy();
virtual void OnLayerUpdate();

private:

};

#endif
