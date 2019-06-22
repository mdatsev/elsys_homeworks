Rails.application.routes.draw do
  resources :subscription_users
  resources :users
  resources :subscriptions
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
