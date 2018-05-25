#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"
#include "Widgets/Input/SComboBox.h"

class IDetailGroup;

/**
* Customizes a CollisionProfileName property to use a dropdown
*/
class FECsBlockchainCommandCustomization : public IPropertyTypeCustomization
{
public:

	FECsBlockchainCommandCustomization();

	static TSharedRef<IPropertyTypeCustomization> MakeInstance();

	/** IPropertyTypeCustomization interface */
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;

protected:

	TSharedRef<SWidget> OnGenerateWidget(TSharedPtr<FString> InItem);

	void OnSelectionChanged(TSharedPtr<FString> NameItem, ESelectInfo::Type SelectInfo);
	void OnComboBoxOpening();

	TSharedPtr<FString> GetSelectedName() const;

	void SetPropertyWithName(const FString& Name);
	void GetPropertyAsName(FString& OutName) const;

	FText GetProfileComboBoxContent() const;

protected:

	TSharedPtr<IPropertyHandle> NameHandle;
	TArray<TSharedPtr<FString>> NameList;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> NameComboBox;
};