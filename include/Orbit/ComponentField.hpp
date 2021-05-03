/*
 * Project: Orbit Engine
 * File: ComponentField.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_COMPONENTFIELD_HPP
#define ORBITENGINE_COMPONENTFIELD_HPP

#define INSPECTOR_FIELD(name, type, field) (this.fields.push_back(new Orbit::ComponentField(type, name, &field)))

namespace Orbit {
    class ComponentField {
    public:
        enum Type {
            String,
            Int,
            Float
        };

        explicit ComponentField(Type type, const char *name, void *dataPtr): type(type), name(name), ptr(dataPtr) {};

        void *getData() const {
            return this->ptr;
        }

        void setData(void *val) {
            switch (this->type) {
                case String:
                    *((const char **)this->ptr) = (const char *) val;
                    break;
                case Int:
                    *((int *)this->ptr) = *(int *) val;
                    break;
                case Float:
                    *((float *)this->ptr) = *(float *) val;
                    break;
            }
        }

        void drawImGuiInspector();

    protected:
        const char *getName() const;

    private:
        const char *name;
        void *ptr;
        Type type;

        static void drawInspector(const char *name, const char **data);
        static void drawInspector(const char *name, int *data);
        static void drawInspector(const char *name, float *data);

    };


}

#endif //ORBITENGINE_COMPONENTFIELD_HPP
