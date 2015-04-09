//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_FORM_H_INCLUDED
#define MK_FORM_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Object/mkIndexer.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkMake.h>
#include <Ui/mkUiForward.h>
#include <Ui/Style/mkStyle.h>

#include <map>

namespace mk
{
	/* Form is the underlying data representation of the UI system
			- name, label and meta text
			- image address
			- ordering of the elements in a collection
	*/

	typedef std::vector<std::unique_ptr<Form>> UniqueFormVector;

    class MK_UI_EXPORT _I_ Form : public TypeObject, public Typed<Form>, public Updatable
    {
	public:
		Form(unique_ptr<Sheet> sheet);
		~Form();

		UiWindow* uiWindow();
		Form* parent() { return mParent; }
		Id index() const { return mIndex; }
		Sheet* sheet() { return mSheet; }
		Sheet* container() { return mContainer; }

		const string& name();

		LrefDict& attrs() { return mAttrs; }
		bool hasAttr(const string& name) { return mAttrs.find(name) != mAttrs.end(); }
		const Lref& getAttr(const string& name) const { if(mAttrs.find(name) != mAttrs.end()) return mAttrs.at(name); else return sNullString; }

		template <class T>
		void setAttr(const string& name, const T& val) { mAttrs.insert(std::make_pair(name, lref(val))); }

		void setIndex(size_t index) { mIndex = index; }

		std::vector<unique_ptr<Form>>& contents() { return mContents; }

		Form* at(size_t index) { return mContents.at(index).get(); }

		void nextFrame(size_t tick, size_t delta);

		// Creation - removal
		void bind(Form* parent);
		void unbind();

		void destroy();
		void clear();
		
		void destroy(size_t index);
		void remove(size_t index);

		void reset(unique_ptr<Sheet> sheet);

		Form* insert(unique_ptr<Form> form, size_t index);
		Form* append(unique_ptr<Form> form);
		unique_ptr<Form> release(size_t index);

		// Indexing
		string concatIndex();

		void move(size_t from, size_t to);
		void reindex(size_t index);

		Form* prev();
		Form* next();

		bool contains(Form* other);

		Form* findParent(Type* type);

		// Specialization
		RootForm* rootForm();

		template <class T, class... Args>
		inline T* emplace(Args&&... args)
		{
			return this->append(make_unique<T>(std::forward<Args>(args)...))->template as<T>();
		}

	public:
		Form* find(const string& search);

	protected:
		Form* mParent;
		size_t mIndex;

		LrefDict mAttrs;

		unique_ptr<Sheet> mUniqueSheet;
		Sheet* mSheet;
		Sheet* mContainer;

		std::vector<unique_ptr<Form>> mContents;

		static Lref sNullString;
    };

	enum FormUpdate
	{
		FORM_DEFAULT = 0,
		FORM_ADDED = 1,
		FORM_REMOVED = 2,
		//FORM_DESTROYED = 3,
		FORM_UPDATED = 3
	};
}

#endif // MK_FORM_H_INCLUDED
