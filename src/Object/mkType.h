//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPE_H_INCLUDED
#define MK_TYPE_H_INCLUDED

/* mk */
#include <Object/mkObjectForward.h>
#include <Object/mkObject.h>

/* Standard */
#include <stdint.h>
#include <memory>

namespace mk
{
	class MK_OBJECT_EXPORT ImprintStub
	{
	public:
		virtual ~ImprintStub() {}
		virtual Imprint* imprint() = 0;
	};

	class MK_OBJECT_EXPORT _I_ Type : public IdObject
	{
	public:
		Type();
		Type(Type& base);
		Type(const string& name);
		Type(const string& name, Type& base);
		~Type();

		_A_ Id id() const { return IdObject::id(); }
		_A_ const string& name() const { return mName; }
		_A_ const Type* base() const { return mBase; }

		Imprint* imprint() { return mImprint; }
		Proto* proto() { return mProto; }
		Indexer* indexer() { return mIndexer; }
		AbstractPool* library() { return mLibrary; }

		Type* base() { return mBase; }

		void setupName(string name) { mName = name; }
		void setupProto(Proto* proto) { mProto = proto; }
		void setupIndexer(Indexer* indexer) { mIndexer = indexer; }
		void setupLibrary(AbstractPool* library) { mLibrary = library; }

		void setupImprint(unique_ptr<ImprintStub> stub) { mImprint = stub->imprint(); mImprintStub = std::move(stub); }

		bool upcast(Type* type);

		static Type& cls() { static Type ty(0); return ty; }

		static size_t maxId() { return sTypeId; }

	private:
		Type(int);

	protected:
		string mName;
		Type* mBase;

		unique_ptr<ImprintStub> mImprintStub;
		Imprint* mImprint;
		Proto* mProto;
		Indexer* mIndexer;
		AbstractPool* mLibrary;

		static size_t sTypeId;
	};
}

#endif // mkTYPE_INCLUDED
